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

int	set_fd(t_cmds *c_tbls, t_token *token)
{
	if ((*token).type == REDIR_IN || (*token).type == REDIR_ADD)
	{
		c_tbls->out = new_fd(token[1].token, (*token).type);
		c_tbls->file_out = ft_strdup(token[1].token);
	}
	else
	{
		c_tbls->in = new_fd(token[1].token, (*token).type);
		c_tbls->file_in = ft_strdup(token[1].token);
	}
	return (0);
}

int	cmds_len(t_cmds *c_tbls, t_token *token, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size && token[i].type == STR)
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

int	set_cmds(t_cmds *c_tbls, t_token *token, unsigned int nb_parsed)
{
	int	size;
	int	i;

	i = 0;
	if (c_tbls->cmds)
		return (0);
	size = cmds_len(c_tbls, token, nb_parsed);
	if (size == 0)
		return (0);
	if (size == -1)
		return (-1);
	while (i < size)
	{
		c_tbls->cmds[i] = ft_strdup(token[i].token);
		i++;
	}
	c_tbls->cmds[i] = 0;
	c_tbls->cmd = ft_strdup(c_tbls->cmds[0]);
	return (i);
}
