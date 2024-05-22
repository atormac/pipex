/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:26:09 by atorma            #+#    #+#             */
/*   Updated: 2024/05/22 18:01:53 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_init(t_pipex_s *px, int argc, char **argv, char **envp)
{
	px->file1 = -1;
	px->file2 = -1;
	px->argc = argc;
	px->argv = argv;
	px->envp = envp;
	px->path = path_get(envp);
	px->pids = pid_init(argc);
	px->pipes = pipes_init(px, argc - 3);
	if (!px->path)
		exit_error(px, PX_ERR_PATH, 0, EXIT_FAILURE);
	if (!px->pids)
		exit_error(px, PX_ERR_PIDS, 0, EXIT_FAILURE);
	if (!px->pipes)
		exit_error(px, PX_ERR_PIPES, 0, EXIT_FAILURE);
}

void	pipex_free_close(t_pipex_s *px)
{
	if (px->file1 >= 0)
		close(px->file1);
	if (px->file2 >= 0)
		close(px->file2);
	pipes_close(px, px->pipes);
	free(px->pids);
	free_array(px->path);
}

void	pipex_dup(t_pipex_s *px, int fd_write, int fd_read)
{
	if (dup2(fd_write, STDOUT_FILENO) == -1)
		exit_error(px, PX_ERR_DUP2, 0, EXIT_FAILURE);
	if (dup2(fd_read, STDIN_FILENO) == -1)
		exit_error(px, PX_ERR_DUP2, 0, EXIT_FAILURE);
}

void	pipex_child(t_pipex_s *px, int i)
{
	if (i == 0)
	{
		px->file1 = open_file1(px);
		pipex_dup(px, px->pipes[i * 2 + 1], px->file1);
	}
	else if ((i + 1) == (px->argc - 3))
	{
		px->file2 = open_file2(px);
		pipex_dup(px, px->file2, px->pipes[(i - 1) * 2]);
	}
	pipes_close(px, px->pipes);
	path_exec(px->argv[i + 2], px);
	exit_silent(px, EXIT_SUCCESS);
}

int	pipex_main(t_pipex_s *px)
{
	int		exit_code;
	int		i;

	i = 0;
	while (i < (px->argc - 3))
	{
		px->pids[i] = fork();
		if (px->pids[i] < 0)
		{
			exit_error(px, PX_ERR_FORK, NULL, EXIT_FAILURE);
			return (0);
		}
		if (px->pids[i] == 0)
			pipex_child(px, i);
		i++;
	}
	pipes_close(px, px->pipes);
	i = 0;
	while (i < px->argc - 3)
		exit_code = pid_wait(px->pids[i++]);
	return (exit_code);
}
