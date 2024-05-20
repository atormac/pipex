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

int	pipex_wait(pid_t pid);

void	pipex_child_one(int *pipefd, int fd_infile, t_env_info *env)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit_child(EXIT_FAILURE, pipefd, fd_infile, env);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		exit_child(EXIT_FAILURE, pipefd, fd_infile, env);
	close(pipefd[1]);
	close(pipefd[0]);
	if (!path_exec(env->argv[2], env))
	{
		error_cmd(env->argv[2]);
		exit_code = EXIT_FAILURE;
	}
	exit_child(exit_code, pipefd, fd_infile, env);
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
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit_child(EXIT_FAILURE, pipefd, out_fd, env);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
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

void	pipex_dup(int f1, int f2)
{
	dup2(f1, STDOUT_FILENO);
	dup2(f2, STDIN_FILENO);
}

void	pipex_child(int i, int *pipes, int fd_infile, t_env_info *env)
{
	int out_fd = -1;

	if (i == 0)
		pipex_dup(pipes[i * 2 + 1], fd_infile);
	else if ((i + 1) == (env->argc - 3))
	{
		out_fd = open(env->argv[env->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (out_fd == -1)
			error_file(env->argv[env->argc - 1]);
		pipex_dup(out_fd, pipes[(i - 1) * 2]);
	}
	else
		pipex_dup(pipes[i * 2 + 1], pipes[(i - 1) * 2]);
	pipes_close(env, pipes);
	if (!path_exec(env->argv[i + 2], env))
		error_cmd(env->argv[i + 2]);
	exit(0);
}


int pipex_main(t_env_info *env, int file1)
{
	int		*pipes;
	int		*pids;
	int		exit_code;
	int		i = 0;

	pipes = pipes_init(env);
	if (!pipes)
		return (0);
	pids = pid_init(env);
	if (!pids)
		return (0);
	while (i < (env->argc - 3))
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (0);
		if (pids[i] == 0)
			pipex_child(i, pipes, file1, env);
		i++;
	}
	pipes_close(env, pipes);
	i = 0;
	while (i < env->argc - 3)
		exit_code = pipex_wait(pids[i++]);
	return (exit_code);
}

int	pipex_wait(pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_info	env;
	int			f1;
	int			code;

	code = EXIT_SUCCESS;
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_SUCCESS);
	}
	if (!envp || !envp[0])
		return (EXIT_SUCCESS);
	f1 = open(argv[1], O_RDONLY, 0644);
	if (f1 == -1)
		error_file(argv[1]);
	env_init(&env, argc, argv, envp);
	code = pipex_main(&env, f1);
	free_array(env.path);
	close(f1);
	return (code);
}
