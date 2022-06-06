#include "minishell.h"

int	new_fd(char *filename, t_token_type type)
{
	int	fd;

	if (type == REDIR_IN || type == REDIR_OUT)
	{
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666 | O_TRUNC);
		if (fd == -1)
			perror(filename);
		return (fd);
	}
	else
	{
		fd = open(filename, O_RDWR | O_APPEND);
		if (fd == -1)
			perror(filename);
		return (fd);
	}
	return (0);
}

t_token_type	choose_tok(char *str)
{
	if (ft_strncmp(">", str, ft_strlen(str)) == 0)
		return (REDIR_IN);
	if (ft_strncmp("<", str, ft_strlen(str)) == 0)
		return (REDIR_OUT);
	if (ft_strncmp(">>", str, ft_strlen(str)) == 0)
		return (REDIR_ADD);
	if (ft_strncmp("<<", str, ft_strlen(str)) == 0)
		return (REDIR_LIM);
	if (ft_strncmp("|", str, ft_strlen(str)) == 0)
		return (PIPE);
	return (0);
}

int	set_fd(t_cmds *c_tbls, char **strs)
{
	if (choose_tok(strs[0]) == REDIR_IN || choose_tok(strs[0]) == REDIR_ADD)
	{
		c_tbls->out = new_fd(strs[1], choose_tok(strs[0]));
		c_tbls->file_out = ft_strdup(strs[1]);
	}
	else
	{
		c_tbls->in = new_fd(strs[1], choose_tok(strs[0]));
		c_tbls->file_in = ft_strdup(strs[1]);
	}
	return (0);
}

int	cmds_len(t_cmds *c_tbls, char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && choose_tok(strs[i]) == 0)
		i++;
	if (i == 0)
		c_tbls->cmds = NULL;
	else
	{
		c_tbls->cmds = malloc(sizeof(char *) * (i + 1));
		if (!c_tbls->cmds)
			return (-1);
	}
	return (i);
}

int	set_cmds(t_cmds *c_tbls, char **strs)
{
	int	size;
	int	i;

	i = 0;
	if (c_tbls->cmds)
		return (0);
	size = cmds_len(c_tbls, strs);
	if (size == 0)
		return (0);
	if (size == -1)
		return (-1);
	while (i < size)
	{
		c_tbls->cmds[i] = ft_strdup(strs[i]);
		i++;
	}
	c_tbls->cmds[i] = 0;
	c_tbls->cmd = ft_strdup(strs[0]);
	return (i);
}
