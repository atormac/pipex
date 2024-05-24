/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:27:18 by atorma            #+#    #+#             */
/*   Updated: 2024/05/24 15:09:24 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	here_doc(t_pipex_s *px, char **argv)
{
	int		fd;
	char	*line;
	int		n;

	fd = open("heredoc", O_CREAT | O_WRONLY | O_EXCL | O_TRUNC, 0644);
	if (fd == -1)
		exit_error(px, PX_ERR_HEREDOC_FILE, 0, 1);
	while (1)
	{
		n = px->cmd_count - 1;
		while (n--)
			write(1, "pipe ", sizeof("pipe ") - 1);
		write(1, "heredoc>", sizeof("heredoc>") - 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	if (!line)
		exit_error(px, PX_ERR_GET_NEXT_LINE, 0, 1);
	free(line);
}

int	open_file1(t_pipex_s *px, int is_heredoc)
{
	int		fd;
	char	*file;

	file = px->argv[1];
	if (is_heredoc)
		file = "heredoc";
	if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
		exit_error(px, PX_ERR_PERMS, file, 126);
	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
		exit_error(px, PX_ERR_FILE, file, 127);
	return (fd);
}

int	open_file2(t_pipex_s *px, int is_heredoc)
{
	int		fd;
	int		flags;
	char	*file;

	flags = O_CREAT | O_WRONLY | O_TRUNC;
	file = px->argv[px->argc - 1];
	if (is_heredoc)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		exit_error(px, PX_ERR_PERMS, file, 126);
	fd = open(file, flags, 0644);
	if (fd == -1)
		exit_error(px, PX_ERR_FILE, file, EXIT_FAILURE);
	return (fd);
}
