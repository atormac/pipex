/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:26:31 by atorma            #+#    #+#             */
/*   Updated: 2024/05/06 17:15:54 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **path_get(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return ft_split(envp[i] + 5, ':');
		i++;
	}
	return (NULL);
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
		error_exit(NULL);
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
		{
			ret = 1;
			break;
		}
		i++;
	}
	free_array(path);
	return (ret);
}

char *path_join(char *path, char *bin)
{
	char	*ret;
	size_t	path_len;
	size_t	bin_len;

	if (!path || ! bin)
		return (NULL);
	path_len = ft_strlen(path);
	bin_len = ft_strlen(path);
	ret = malloc(path_len + bin_len + 2);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, path, path_len + 1);
	ft_strlcat(ret, "/", path_len + bin_len + 2);
	ft_strlcat(ret, bin, path_len + bin_len + 2);
	return (ret);
}
