#include "tester.h"

int	main(int ac, char **av, char **env)
{
	int	fd;
	char	*line;
	char	*buff;
	pid_t	minishell;
	pid_t	posix;
	int	pfd[2];
	int	pfd1[2];

	pipe(pfd);
	pipe(pfd1);
	minishell = fork();
	posix = fork();
	if (minishell == 0)
	{
		close(pfd[1]);
		close(pfd1[0]);
		close(pfd1[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		execve("../minishell", NULL, env);
	}
	if (posix == 0)
	{
		close(pfd[1]);
		close(pfd[0]);
		close(pfd1[1]);
		dup2(pfd1[0], 0);
		close(pfd1[0]);
		execve("bash", &ft_strdup("--posix"), env);
	}
	if (minishell > 0 && posix > 0)
	{
		fd = open("tester.sh", O_RDONLY);
		close(pfd[0]);
		close(pfd1[0]);
		while (get_next_line(fd, &line))
		{
			write(pfd[1], line(ft_strlen(line));
			write(pfd[1], "\n", 1);
			write(pfd1[1], line(ft_strlen(line);
			write(pfd1[1], "\n", 1);
			readline("ENTER");
			free(line);
		}
		wait(0);
	}
	return (0);
}



	
