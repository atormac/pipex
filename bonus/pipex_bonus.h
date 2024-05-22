/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:27:39 by atorma            #+#    #+#             */
/*   Updated: 2024/05/22 15:11:11 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

enum
{
	PX_ERR_FILE,
	PX_ERR_PERMS,
	PX_ERR_CMD,
	PX_ERR_FORK,
	PX_ERR_DUP2,
	PX_ERR_MALLOC,
	PX_ERR_PATH,
	PX_ERR_PIDS,
	PX_ERR_PIPES,
	PX_ERR_HEREDOC_FILE,
	PX_ERR_GET_NEXT_LINE
};

typedef struct t_pipex_s
{
	int		file1;
	int		file2;
	int		cmd_count;
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
int		*pid_init(int cmd_count);
int		*pipes_init(int cmd_count);
int		pid_wait(pid_t pid);
void	pipes_close(t_pipex_s *px, int *pipes);
char	**path_get(char **envp);
char	*path_join(char *path, char *bin);
int		path_exec(char *cmd, t_pipex_s *px);
void	free_array(char **arr);
int		here_doc(t_pipex_s *px, char **argv);
int		open_file1(t_pipex_s *px, int is_heredoc);
int		open_file2(t_pipex_s *px, int is_heredoc);
void	error_output(int error, char *str);
void	exit_error(t_pipex_s *px, int error, char *str, int code);
void	exit_silent(t_pipex_s *px, int code);

#endif
