/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:25:55 by atorma            #+#    #+#             */
/*   Updated: 2024/05/22 18:05:47 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*pid_init(int argc)
{
	int	cmd_count;

	cmd_count = argc - 3;
	return (malloc(cmd_count * sizeof(int)));
}

int	pid_wait(pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	*pipes_init(t_pipex_s *px, int cmd_count)
{
	int	i;
	int	*pipes;

	i = 0;
	pipes = malloc((cmd_count - 1) * (2 * sizeof(int)));
	if (!pipes)
		exit_error(px, PX_ERR_MALLOC, "pipes_init", 1);
	while (pipes && i < (cmd_count - 1))
	{
		if (pipe(pipes + (i * 2)) < 0)
		{
			i--;
			while (i >= 0)
			{
				close(pipes[i * 2]);
				close(pipes[i * 2 + 1]);
				i--;
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	pipes_close(t_pipex_s *px, int *pipes)
{
	int	cmd_count;
	int	i;
	int	*pipefd;

	i = 0;
	cmd_count = px->argc - 3;
	if (!pipes)
		return ;
	while (i < (cmd_count - 1))
	{
		pipefd = pipes + (i * 2);
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
	}
	free(pipes);
	px->pipes = NULL;
}
