/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:26:31 by atorma            #+#    #+#             */
/*   Updated: 2024/05/24 19:51:12 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_get(t_pipex_s *px, char **envp)
{
	int		i;
	char	**arr;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			arr = ft_split(envp[i] + 5, ':');
			if (!arr)
				exit_error(px, PX_ERR_MALLOC, "ft_split", 1);
			return (arr);
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
		exit_error(px, PX_ERR_MALLOC, "split", EXIT_FAILURE);
	cmd = path_join(path, arg_arr[0]);
	if (!cmd)
	{
		free_array(arg_arr);
		exit_error(px, PX_ERR_MALLOC, "path_join", EXIT_FAILURE);
	}
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) != 0)
			ret = -1;
		else if (execve(cmd, arg_arr, px->envp) != -1)
			ret = 1;
	}
	free_array(arg_arr);
	free(cmd);
	return (ret);
}

void	path_error(int ret, char *cmd, t_pipex_s *px)
{
	char	*sp;
	size_t	len;

	sp = ft_strchr(cmd, ' ');
	if (sp)
		cmd[sp - cmd] = 0;
	if (ret == 0)
	{
		if (cmd)
		{
			len = ft_strlen(cmd);
			if (len && cmd[len - 1] == '/')
				exit_error(px, PX_ERR_DIR, cmd, 127);
		}
		exit_error(px, PX_ERR_CMD, cmd, 127);
	}
	if (ret == -1)
		exit_error(px, PX_ERR_PERMS, cmd, 126);
}

int	path_exec(char *cmd, t_pipex_s *px)
{
	int		ret;
	int		i;
	char	*slash;

	ret = 0;
	i = 0;
	slash = NULL;
	if (cmd)
		slash = ft_strchr(cmd, '/');
	if (!px->path || slash)
	{
		ret = exec_cmd("", cmd, px);
	}
	while (px->path && !slash && px->path[i])
	{
		ret = exec_cmd(px->path[i], cmd, px);
		if (ret == 1 || ret == -1)
			break ;
		i++;
	}
	if (ret == 0 || ret == -1)
		path_error(ret, cmd, px);
	return (ret);
}

char	*path_join(char *path, char *bin)
{
	char	*ret;
	size_t	path_len;
	size_t	bin_len;

	path_len = ft_strlen(path);
	bin_len = ft_strlen(bin);
	ret = malloc(path_len + bin_len + 2);
	if (!ret)
		return (NULL);
	if (bin && ft_strchr(bin, '/'))
	{
		ft_strlcpy(ret, bin, bin_len + 1);
		return (ret);
	}
	ft_strlcpy(ret, path, path_len + 1);
	ft_strlcpy(ret + path_len, "/", 2);
	ft_strlcpy(ret + path_len + 1, bin, bin_len + 1);
	return (ret);
}
