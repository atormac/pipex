/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:57:50 by atorma            #+#    #+#             */
/*   Updated: 2024/05/05 19:41:00 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//argv[1] = infile
//argv[2] = cmd1
//argv[3] = cmd2
//argv[4] = outfile

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int exec_cmd(char *path, char *bin, char **envp)
{
	int		ret;
	char	*cmd;
	char	**arg_arr;

	ret = 0;
	arg_arr = ft_split(bin, ' ');
	if (!arg_arr)
		return (0);
	cmd = path_join(path, arg_arr[0]);
	if (!cmd)
	{
		free_array(arg_arr);
		return (0);
	}
	if (execve(cmd, arg_arr, envp) != -1)
		ret = 1;
	free(arg_arr);
	free(cmd);
	return (ret);
}

int path_find_exec(char *cmd, char **envp)
{
	char	**path;
	int		ret;
	int		i;

	ret = 0;
	path = path_get(envp);
	if (!path)
		return (ret);
	i = 0;
	while (path[i])
	{
		if (exec_cmd(path[i], cmd, envp) == 1)
			break;
		i++;
	}
	free_array(path);
	return (ret);
}

void pipex_main(int f1, int f2, char **argv, char **envp)
{
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid < 0)
		return (perror("fork()"));
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		dup2(f1, STDIN_FILENO);
		close(pipefd[0]);
		path_find_exec(argv[2], envp);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(pipefd[1]);
	path_find_exec(argv[3], envp);
}

int main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (0);
	}
	f1 = open(argv[1], O_RDONLY, 0777);
	f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (f1 < 0 || f2 < 0)
		return (0);
	pipex_main(f1, f2, argv, envp);
	close(f1);
	close(f2);
	return (0);
}
