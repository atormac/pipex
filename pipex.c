/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:26:09 by atorma            #+#    #+#             */
/*   Updated: 2024/05/06 14:54:33 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//argv[1] = infile
//argv[2] = cmd1
//argv[3] = cmd2
//argv[4] = outfile

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
		if (dup2(pipefd[1], STDOUT_FILENO) == -1 || dup2(f1, STDIN_FILENO) == -1)
			return (perror("dup2()"));
		close(pipefd[0]);
		path_find_exec(argv[2], envp);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	if (dup2(pipefd[0], STDIN_FILENO) == -1 || dup2(f2, STDOUT_FILENO) == -1)
		return (perror("dup2()"));
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
	{
		perror("open");
		return (0);
	}
	pipex_main(f1, f2, argv, envp);
	close(f1);
	close(f2);
	return (0);
}
