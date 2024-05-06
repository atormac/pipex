/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:24:37 by atorma            #+#    #+#             */
/*   Updated: 2024/05/06 16:50:01 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
#define FT_PIPEX_H
#include "./libft/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char	**path_get(char **envp);
char	*path_join(char *path, char *bin);
int		path_find_exec(char *cmd, char **envp);
void	free_array(char **arr);
void	error_exit(char *str);

#endif
