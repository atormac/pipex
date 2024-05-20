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

void	error_output(int error, char *str)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (error == PX_ERR_FILE)
		ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
	else if (error == PX_ERR_CMD)
		ft_putstr_fd("command not found: ", STDERR_FILENO);
	else if (error == PX_ERR_FORK)
		ft_putstr_fd("fork() error", STDERR_FILENO);
	else if (error == PX_ERR_DUP2)
		ft_putstr_fd("dup2() error", STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void exit_error(t_pipex_s *px, int error, char *str, int code)
{
	error_output(error, str);
	pipex_free_close(px);
	exit(code);
}

void exit_silent(t_pipex_s *px, int code)
{
	pipex_free_close(px);
	exit(code);
}
