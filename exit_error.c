/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:37:21 by atorma            #+#    #+#             */
/*   Updated: 2024/05/18 20:00:36 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exit_error(t_pipex_s *px, int code)
{
	pipex_free_close(px);
	exit(code);
}

void	error_cmd(char *cmd)
{
	char	*sp;

	sp  = ft_strchr(cmd, ' ');
	if (sp)
		cmd[sp - cmd] = '\0';
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	error_file(char *cmd)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	error_exit(char *str)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
	{
		perror(NULL);
	}
	exit(EXIT_FAILURE);
}
