/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:00:36 by atorma            #+#    #+#             */
/*   Updated: 2024/05/21 17:07:23 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
int	here_doc(char **argv)
{
	int	fd;

	fd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (0);
	dup2(fd, STDIN_FILENO);
	while (1)
	{
		line = get_next_line(
		if (strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break;
		write(fd, line, ft_strlen(line));
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_s	px;
	int			code;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(argv[1], "here_doc", sizeof("here_doc") - 1) == 0)
	{
		ft_putstr_fd("heredoc1", 1);
		int fd_here = open(STDIN_FILENO, O_RDONLY);
		if (fd_here == -1)
		{
			ft_putstr_fd("could not open stdin!\n", 1);
		}
		return (EXIT_SUCCESS);
	}
	code = EXIT_FAILURE;
	pipex_init(&px, argc, argv, envp);
	code = pipex_main(&px);
	pipex_free_close(&px);
	return (code);
}
