/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:21:25 by atorma            #+#    #+#             */
/*   Updated: 2024/05/18 17:46:59 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	env_init(t_env_info *env, char **argv, char **envp)
{
	env->argv = argv;
	env->envp = envp;
	env->path = path_get(envp);
	if (env->path == NULL)
		return (0);
	return (1);
}

void	exit_child(int code, int *pipefd, int fd, t_env_info* env)
{
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
	free_array(env->path);
	exit(code);
}

void	error_cmd(char *cmd)
{
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
