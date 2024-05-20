#include "pipex.h"


int *pid_init(t_env_info *env)
{
	int	cmd_count;

	cmd_count = env->argc - 3;
	return (malloc(cmd_count * sizeof(int)));
}

int *pipes_init(t_env_info *env)
{
	int i = 0;
	int cmd_count = env->argc - 3;
	int	*pipes = malloc((cmd_count - 1) * (2 * sizeof(int)));
	
	if (!pipes)
		return (NULL);
	while (i < (cmd_count - 1))
	{
		ft_putstr_fd("pipe allocated\n", 1);
		if (pipe(pipes + (i * 2)) < 0)
		{
			ft_putstr_fd("pipe() failed\n", 1);
		}
		i++;
	}
	return (pipes);
}

void pipes_close(t_env_info *env, int *pipes)
{
	int cmd_count = env->argc - 3;
	int i = 0;
	while (i < (cmd_count - 1))
	{
		int *pipefd = pipes + (i * 2);
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
	}
	free(pipes);
}
