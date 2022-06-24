#include "minishell.h"

int	exec_errors(int status_code, const char *cmd)
{
	(void)status_code;
	int	fd;

	fd = 0;
	write(2, "bash: ", 6);
	if (errno == 2 && ft_strchr(cmd, '/') != NULL)
	{
		perror(cmd);
		return (127);
	}
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == -1)
		{
			perror(cmd);
			return (126);
		}
		fd = open(cmd, O_DIRECTORY);
		if (fd != -1)
		{
			close(fd);
			write(2, cmd, ft_strlen(cmd));
			write(2, ": ", 2);
			write(2, "Is a directory\n", ft_strlen("Is a directory\n"));
			return (126);
		}
	}
	if (errno == 2)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, "command not found\n", ft_strlen("command not found\n"));
		return (127);
	}
	if (errno == 13)
	{
		perror(cmd);
		write(2, "Permission denied\n", 18);
		return (126);
	}
	
	return (EXIT_FAILURE);
}
