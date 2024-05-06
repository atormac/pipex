/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:21:25 by atorma            #+#    #+#             */
/*   Updated: 2024/05/06 18:09:23 by atorma           ###   ########.fr       */
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

void	error_exit(char *str)
{
	if (str)
		fprintf(stderr, "%s: %s\n", strerror(errno), str);
	else
		fprintf(stderr, "%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}
