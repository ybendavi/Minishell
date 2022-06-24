#include "minishell.h"

int	exec_errors(int status_code, const char *cmd)
{
	write(2, "bash:", 5);
	write(2, cmd, ft_strlen(cmd));
	write(2, ":", 1);
	if (status_code == 127)
		write(2, "command not found\n", 18);
	if (status_code == 126)
		write(2, "Permission denied\n", 18);
	return (0);
}
