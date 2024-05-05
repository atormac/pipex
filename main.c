/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:57:50 by atorma            #+#    #+#             */
/*   Updated: 2024/05/05 19:38:28 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>

void args_print(int argc, char **argv);

char *cmd1[] = { "/bin/ls", "-l", 0 };

void pipe_handle(int pipefd[2], int pid, char **argv)
{
	char rb[2048] = { 0 };
	if (pid == 0) //child
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		//printf("argv[1]: %s\n", argv[1]);
		execve(argv[1], &argv[1], NULL);

	}
	else //parent
	{
		close(pipefd[1]);	
		read(pipefd[0], rb, 2048);
		ft_putstr_fd(rb, 1);
		close(pipefd[0]);
	}

}

int main(int argc, char **argv)
{
	int pipefd[2];
	int	pid;

	if (argc != 3)
		return (0);
	if (pipe(pipefd) < 0)
	{
		ft_putstr_fd("pipe creation failed\n", 1);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork() returned -1\n", 1);
		return (-1);
	}

	pipe_handle(pipefd, pid, argv);
	//args_print(argc, argv);
	return (0);
}
