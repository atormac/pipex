/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:21:25 by atorma            #+#    #+#             */
/*   Updated: 2024/05/21 19:33:24 by atorma           ###   ########.fr       */
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

int open_file1(t_pipex_s *px)
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
	int	fd;
	int	flags;

	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (access(px->argv[px->argc -1], F_OK) == 0 && access(px->argv[px->argc -1], W_OK) == -1)
		exit_error(px, PX_ERR_PERMS, px->argv[px->argc - 1], 126);
	fd = open(px->argv[px->argc - 1], flags, 0644);
	if (fd == -1)
		exit_error(px, PX_ERR_FILE, px->argv[px->argc - 1], EXIT_FAILURE);
	return fd;
}
