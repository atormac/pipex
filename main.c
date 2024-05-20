#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex_s	px;
	int			code;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_SUCCESS);
	}
	code = EXIT_FAILURE;
	pipex_init(&px, argc, argv, envp);
	code = pipex_main(&px);
	pipex_free_close(&px);
	return (code);
}