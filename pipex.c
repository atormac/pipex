/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:26:09 by atorma            #+#    #+#             */
/*   Updated: 2024/05/18 19:31:38 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_init(t_pipex_s *px, int argc, char **argv, char **envp)
{
	px->file1 = -1;
	px->file2 = -1;
	px->argc = argc;
	px->argv = argv;
	px->envp = envp;
	px->path = path_get(envp);
	px->pids = pid_init(argc);
	px->pipes = pipes_init(argc);
	if (!px->path || !px->pids || !px->pipes)
		return (0);
	return (1);
}

void pipex_free_close(t_pipex_s *px)
{
	pipes_close(px, px->pipes);
	free(px->pids);
	free_array(px->path);
	if (px->file1 >= 0)
		close(px->file1);
	if (px->file2 >= 0)
		close(px->file2);
}

void	pipex_dup(t_pipex_s *px, int fd_write, int fd_read)
{
	if (dup2(fd_write, STDOUT_FILENO) == -1)
		exit_error(px, PX_ERR_DUP2, 0, EXIT_FAILURE);
	if (dup2(fd_read, STDIN_FILENO) == -1)
		exit_error(px, PX_ERR_DUP2, 0, EXIT_FAILURE);
}

void	pipex_child(t_pipex_s *px, int file1, int i)
{
	if (i == 0)
		pipex_dup(px, px->pipes[i * 2 + 1], file1);
	else if ((i + 1) == (px->argc - 3))
	{
		px->file2 = open(px->argv[px->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (px->file2 == -1)
			exit_error(px, PX_ERR_FILE, px->argv[px->argc - 1], EXIT_FAILURE);
		pipex_dup(px, px->file2, px->pipes[(i - 1) * 2]);
	}
	else
		pipex_dup(px, px->pipes[i * 2 + 1], px->pipes[(i - 1) * 2]);
	pipes_close(px, px->pipes);
	if (!path_exec(px->argv[i + 2], px))
		exit_error(px, PX_ERR_CMD, px->argv[i + 2], 127);
	pipex_free_close(px);
	exit(EXIT_SUCCESS);
}


int pipex_main(t_pipex_s *px, int file1)
{
	int		exit_code;
	int		i = 0;

	px->file1 = file1;
	while (i < (px->argc - 3))
	{
		px->pids[i] = fork();
		if (px->pids[i] < 0)
		{
			exit_error(px, PX_ERR_FORK, NULL, EXIT_FAILURE);
			return (0);
		}
		if (px->pids[i] == 0)
			pipex_child(px, file1, i);
		i++;
	}
	pipes_close(px, px->pipes);
	i = 0;
	while (i < px->argc - 3)
		exit_code = pid_wait(px->pids[i++]);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_s	px;
	int			f1;
	int			code;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_SUCCESS);
	}
	code = EXIT_FAILURE;
	f1 = open(argv[1], O_RDONLY, 0644);
	if (f1 == -1)
		error_output(PX_ERR_FILE, argv[1]);
	if (pipex_init(&px, argc, argv, envp))
		code = pipex_main(&px, f1);
	pipex_free_close(&px);
	return (code);
}
