#include "pipex.h"

char **path_get(char **envp)
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
