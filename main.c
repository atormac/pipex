/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atorma <atorma@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:57:50 by atorma            #+#    #+#             */
/*   Updated: 2024/05/05 19:41:00 by atorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>

void args_print(int argc, char **argv);

char **get_path_env(char **envp)
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

int exec_cmd(char **argv, char **envp)
{
	char	**env_paths;
	int		ret;
	int		i;

	ret = 0;
	env_paths = get_path_env(envp);
	if (!env_paths)
		return (ret);
	i = 0;
	while (env_paths[i])
	{
		char *cmd = path_join(env_paths[i], argv[1]);
		if (!cmd)
			break;
		if (execve(cmd, &argv[1], envp) != -1)
		{
			free(cmd);
			ret = 1;
			break;
		}
		free(cmd);
		i++;
	}
	return (ret);
}

void pipe_handle(int pipefd[2], int pid, char **argv, char **envp)
{
	char rb[2048] = { 0 };

	if (pid == 0) //child
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		//close(pipefd[1]);
		exec_cmd(argv, envp);
	}
	else //parent
	{
		close(pipefd[1]);	
		read(pipefd[0], rb, 2048);
		ft_putstr_fd(rb, 1);
		close(pipefd[0]);
	}

}

int main(int argc, char **argv, char **envp)
{
	int pipefd[2];
	int	pid;

	if (argc != 3)
		return (0);
	if (pipe(pipefd) < 0)
	{
		ft_putstr_fd("pipe creation failed\n", 1);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork() returned -1\n", 1);
		return (-1);
	}

	pipe_handle(pipefd, pid, argv, envp);
	//args_print(argc, argv);
	return (0);
}
