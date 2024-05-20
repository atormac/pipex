/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:26:31 by atorma            #+#    #+#             */
/*   Updated: 2024/05/18 18:57:30 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_get(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			if ((envp[i] + 5) == NULL)
				break;
			return (ft_split(envp[i] + 5, ':'));
		}
		i++;
	}
	return (NULL);
}

int	exec_cmd(char *path, char *bin, t_pipex_s *px)
{
	int		ret;
	char	*cmd;
	char	**arg_arr;

	ret = 0;
	arg_arr = ft_split(bin, ' ');
	if (!arg_arr)
		exit_error(px, EXIT_FAILURE);
	cmd = path_join(path, arg_arr[0]);
	if (!cmd)
	{
		free_array(arg_arr);
		exit_error(px, EXIT_FAILURE);
	}
	if (access(cmd, F_OK) == 0)
	{
		if (execve(cmd, arg_arr, px->envp) != -1)
			ret = 1;
	}
	free_array(arg_arr);
	free(cmd);
	return (ret);
}

int	path_exec(char *cmd, t_pipex_s *px)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (px->path[i])
	{
		if (exec_cmd(px->path[i], cmd, px) == 1)
		{
			ret = 1;
			break ;
		}
		i++;
	}
	return (ret);
}

char	*path_join(char *path, char *bin)
{
	char	*ret;
	size_t	path_len;
	size_t	bin_len;

	if (!path || ! bin)
		return (NULL);
	path_len = ft_strlen(path);
	bin_len = ft_strlen(bin);
	ret = malloc(path_len + bin_len + 2);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, path, path_len + 1);
	ft_strlcpy(ret + path_len, "/", 2);
	ft_strlcpy(ret + path_len + 1, bin, bin_len + 1);
	return (ret);
}
