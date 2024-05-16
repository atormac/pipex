/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:24:37 by atorma            #+#    #+#             */
/*   Updated: 2024/05/16 20:39:17 by atorma           ###   ########.fr       */
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

typedef struct t_env_info
{
	char	**argv;
	char	**envp;
	char	**path;
}	t_env_info;

char	**path_get(char **envp);
char	*path_join(char *path, char *bin);
int		path_exec(char *cmd, t_env_info *env);
void	free_array(char **arr);
int		env_init(t_env_info *env, char **argv, char **envp);
void	error_cmd(char *cmd);
void	error_file(char *cmd);
void	error_exit(char *str);

#endif
