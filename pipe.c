#include "pipex.h"


int *pid_init(int argc)
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

int *pipes_init(int argc)
{
	int i = 0;
	int cmd_count = argc - 3;
	int	*pipes = malloc((cmd_count - 1) * (2 * sizeof(int)));
	
	if (!pipes)
		return (NULL);
	while (i < (cmd_count - 1))
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

void pipes_close(t_pipex_s *px, int *pipes)
{
	int cmd_count = px->argc - 3;
	int i = 0;
	int	*pipefd;

	if (!pipes)
		return;
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
