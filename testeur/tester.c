#include "tester.h"

int	main(int ac, char **av, char **env)
{
	int	fd;
	char	*line;
	char	*buff;
	pid_t	minishell;
	pid_t	posix;
	char	**bash_args;
	char 	**min_args;
	int	pfd[2];
	int	pfd1[2];
	int	pfd2[2];
	int	pfd3[2];
	char	*buffer;
	int	ret;
	int	i;

	pipe(pfd);
	pipe(pfd1);
	pipe(pfd2);
	pipe(pfd3);
	line = NULL;
	bash_args = malloc(sizeof(char **) * 3);
	bash_args[0] = ft_strdup("bash");
	bash_args[1] = ft_strdup("--posix");
	bash_args[2] = NULL;
	min_args = malloc(sizeof(char **) * 2);
	min_args[0] = ft_strdup("minishell");
	min_args[1] = NULL;
	buffer = ft_calloc(sizeof(char) * 10000);
	minishell = fork();
	if (minishell == 0)
	{
		close(pfd3[0]);
		close(pfd3[1]);
		close(pfd2[0]);
		close(pfd[1]);
		close(pfd1[0]);
		close(pfd1[1]);
		dup2(pfd[0], 0);
		dup2(pfd2[1], 1);
		close(pfd2[1]);
		close(pfd[0]);
		execve("../minishell", min_args, env);
	}
	posix = fork();
	if (posix == 0)
	{
		close(pfd2[0]);
		close(pfd2[1]);
		close(pfd3[0]);
		close(pfd[1]);
		close(pfd[0]);
		close(pfd1[1]);
		dup2(pfd1[0], 0);
		dup2(pfd3[1], 1);
		close(pfd3[1]);
		close(pfd1[0]);
		execve("/bin/bash", bash_args, env);
	}
	if (minishell > 0 && posix > 0)
	{
		fd = open("test.sh", O_RDONLY);
		close(pfd[0]);
		close(pfd1[0]);
		close(pfd2[1]);
		close(pfd3[1]);
		while (get_next_line(fd, &line))
		{
			write(pfd[1], line, ft_strlen(line));
			write(pfd[1], "\n", 1);
			write(pfd1[1], line, ft_strlen(line));
			write(pfd1[1], "\n", 1);
			i = 0;
			while (read(pfd2[0], &buffer[i], 1) > 0)
				i++;
			printf("minishell_out:%s\n", buffer);
			ft_bzero(buffer, i);
			i  = 0;
			while (read(pfd3[0], &buffer[i], 1) > 0)
				i++;
			printf("posix_out:%s\n", buffer);
			ft_bzero(buffer, i);
			readline("ENTER");
			free(line);
		}
		wait(0);
		close(fd);
		fd = 0;
		while (bash_args[fd])
		{
			free(bash_args[fd]);
			fd++;
		}
		free(bash_args);
		free(min_args[0]);
		free(min_args);
	}
	return (0);
}
