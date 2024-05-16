/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:26:09 by atorma            #+#    #+#             */
/*   Updated: 2024/05/16 16:01:05 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_child_one(int *pipefd, int f1, t_env_info *env)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (dup2(pipefd[1], STDOUT_FILENO) == -1 || dup2(f1, STDIN_FILENO) == -1)
	{
		free_array(env->path);
		error_exit(NULL);
	}
	close(pipefd[0]);
	if (!path_exec(env->argv[2], env))
	{
		error_cmd(env->argv[2]);
		exit_code = EXIT_FAILURE;
	}
	free_array(env->path);
	exit(exit_code);
}

void	pipex_child_two(int *pipefd, int f2, t_env_info *env)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (dup2(pipefd[0], STDIN_FILENO) == -1 || dup2(f2, STDOUT_FILENO) == -1)
	{
		free_array(env->path);
		return (error_exit(NULL));
	}
	close(pipefd[1]);
	if (!path_exec(env->argv[3], env))
	{
		error_cmd(env->argv[3]);
		exit_code = EXIT_FAILURE;
		close(pipefd[1]);
	}
	free_array(env->path);
	exit(exit_code);
}

int	pipex_main(int f1, int f2, t_env_info *env)
{
	int		status;
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
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		close(pipefd[0]);
		return (0);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (0);
	if (pid2 == 0)
		pipex_child_two(pipefd, f2, env);
	close(pipefd[0]);
	waitpid(pid2, NULL, 0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_info	env;
	int			f1;
	int			f2;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_SUCCESS);
	}
	f1 = open(argv[1], O_RDONLY, 0777);
	if (f1 == -1)
		error_exit(argv[1]);
	f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (f2 == -1)
		error_exit(argv[4]);
	if (env_init(&env, argv, envp))
		pipex_main(f1, f2, &env);
	free_array(env.path);
	close(f1);
	close(f2);
	return (EXIT_SUCCESS);
}
