/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:21:25 by atorma            #+#    #+#             */
/*   Updated: 2024/05/26 17:05:17 by atorma           ###   ########.fr       */
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

char	*cmd_has_slash(char *cmd)
{
	char	*sp;
	char	*slash;

	sp = ft_strchr(cmd, ' ');
	slash = ft_strchr(cmd, '/');
	if (sp && slash)
	{
		if (sp <= slash)
			return (NULL);
	}
	return (slash);
}

int	open_file1(t_pipex_s *px)
{
	int		fd;
	char	*file;

	file = px->argv[1];
	if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
		exit_error(px, PX_ERR_PERMS, file, 126);
	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
		exit_error(px, PX_ERR_FILE, file, 127);
	return (fd);
}

int	open_file2(t_pipex_s *px)
{
	int		fd;
	int		flags;
	char	*file;

	flags = O_CREAT | O_WRONLY | O_TRUNC;
	file = px->argv[px->argc - 1];
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		exit_error(px, PX_ERR_PERMS, file, 126);
	fd = open(file, flags, 0644);
	if (fd == -1)
		exit_error(px, PX_ERR_FILE, file, EXIT_FAILURE);
	return (fd);
}
