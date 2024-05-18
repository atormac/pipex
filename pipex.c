/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:26:09 by atorma            #+#    #+#             */
/*   Updated: 2024/05/18 18:36:21 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_child_one(int *pipefd, int f1, t_env_info *env)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (dup2(pipefd[1], STDOUT_FILENO) == -1 || dup2(f1, STDIN_FILENO) == -1)
		exit_child(EXIT_FAILURE, pipefd, f1, env);
	close(pipefd[1]);
	close(pipefd[0]);
	if (!path_exec(env->argv[2], env))
	{
		error_cmd(env->argv[2]);
		exit_code = EXIT_FAILURE;
	}
	exit_child(exit_code, pipefd, f1, env);
}

void	pipex_child_two(int *pipefd, t_env_info *env)
{
	int	exit_code;
	int	out_fd;

	exit_code = EXIT_SUCCESS;
	out_fd = open(env->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out_fd == -1)
	{
		error_file(env->argv[4]);
		exit_child(EXIT_FAILURE, pipefd, out_fd, env);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1 || dup2(out_fd, STDOUT_FILENO) == -1)
		exit_child(EXIT_FAILURE, pipefd, out_fd, env);
	close(pipefd[1]);
	close(pipefd[0]);
	if (!path_exec(env->argv[3], env))
	{
		error_cmd(env->argv[3]);
		exit_code = 127;
	}
	exit_child(exit_code, pipefd, out_fd, env);
}

int	pipex_wait(pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	pipex_main(int f1, t_env_info *env)
{
	int		pipefd[2];
	pid_t	pid;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		pipex_child_one(pipefd, f1, env);
	pid2 = fork();
	if (pid2 == -1)
		return (0);
	if (pid2 == 0)
		pipex_child_two(pipefd, env);
	close(pipefd[1]);
	close(pipefd[0]);
	pipex_wait(pid);
	return pipex_wait(pid2);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_info	env;
	int			f1;
	int			code;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_SUCCESS);
	}
	f1 = open(argv[1], O_RDONLY, 0644);
	if (f1 == -1)
		error_file(argv[1]);
	env_init(&env, argv, envp);
	code = pipex_main(f1, &env);
	free_array(env.path);
	close(f1);
	return (code);
}
