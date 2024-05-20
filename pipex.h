/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:24:37 by atorma            #+#    #+#             */
/*   Updated: 2024/05/18 17:47:05 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

enum
{
	PX_ERR_FILE,
	PX_ERR_CMD,
	PX_ERR_FORK,
	PX_ERR_DUP2,
	PX_ERR_MALLOC,
	PX_ERR_PATH,
	PX_ERR_PIDS,
	PX_ERR_PIPES
};

typedef struct t_pipex_s
{
	int		file1;
	int		file2;
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
	int		*pipes;
	int		*pids;
}	t_pipex_s;

void	pipex_init(t_pipex_s *px, int argc, char **argv, char **envp);
int		pipex_main(t_pipex_s *px);
void	pipex_free_close(t_pipex_s *px);
int		*pid_init(int argc);
int		pid_wait(pid_t pid);
int		*pipes_init(int argc);
void	pipes_close(t_pipex_s *px, int *pipes);
char	**path_get(char **envp);
char	*path_join(char *path, char *bin);
int		path_exec(char *cmd, t_pipex_s *px);
void	free_array(char **arr);
void	error_output(int error, char *str);
void	exit_error(t_pipex_s *px, int error, char *str, int code);
void	exit_silent(t_pipex_s *px, int code);

#endif
