#include "tester.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if ((!s1 && s2) || (!s2 && s1))
		return (1);
	if (!s1 && !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	fd;
	char	*line;
	char	*buff;
	pid_t	minishell;
	pid_t	posix;
	pid_t	read_f;
	char	**bash_args;
	char 	**min_args;
	int	pfd[2];
	int	pfd1[2];
	int	fd_min;
	int	fd_pos;
	char	*buffer;
	int	ret;
	int	i;
	int	status;

	pipe(pfd);
	pipe(pfd1);
	fd_min = open("minishell_out", O_RDWR | O_CREAT, 0666 | O_APPEND);
	fd_pos = open("pos_out", O_RDWR | O_CREAT, 0666 | O_APPEND);
	line = NULL;
	bash_args = malloc(sizeof(char **) * 6);
	bash_args[0] = ft_strdup("bash");
	bash_args[1] = ft_strdup("--posix");
	bash_args[2] = NULL;
	min_args = malloc(sizeof(char **) * 2);
	min_args[0] = ft_strdup("minishell");
	min_args[1] = NULL;
	buffer = ft_calloc(sizeof(char),  1000000);
	minishell = fork();
	if (minishell == 0)
	{
		close(pfd[1]);
		close(pfd1[0]);
		close(pfd1[1]);
		dup2(pfd[0], 0);
		dup2(fd_min, 1);
		dup2(fd_min, 2);
		close(pfd[0]);
		execve("../minishell", min_args, env);
	}
	posix = fork();
	if (posix == 0)
	{
		close(pfd[1]);
		close(pfd[0]);
		close(pfd1[1]);
		dup2(pfd1[0], 0);
		dup2(fd_pos, 1);
		dup2(fd_pos, 2);
		close(pfd1[0]);
		execve("/bin/bash", bash_args, env);
	}
	if (minishell > 0 && posix > 0)
	{
		fd = open("test.sh", O_RDONLY);
		close(pfd[0]);
		close(pfd1[0]);
		while (get_next_line(fd, &line))
		{
			write(pfd[1], line, ft_strlen(line));
			write(pfd[1], "\n", 1);
			write(pfd1[1], line, ft_strlen(line));
			write(pfd1[1], "\n", 1);
			free(line);
		}
		wait(&status);
		close(fd);
		close(fd_min);
		close(fd_pos);
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
