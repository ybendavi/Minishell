/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_assets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:28:03 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/10 16:43:30 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_fds_list(t_cmds *cmd, int fd)
{
	t_fds	*tmp;

	if (!cmd->fds)
	{
		cmd->fds = ft_calloc(sizeof(t_fds) * 1);
		if (!cmd->fds)
			return (-1);
		cmd->fds->fd = fd;
		cmd->fds->next = NULL;
	}
	if (cmd->fds)
	{
		tmp = cmd->fds;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_calloc(sizeof(t_fds) * 1);
		if (!tmp->next)
			return (-1);
		tmp->next->fd = fd;
		tmp->next->next = NULL;
	}
	return (0);
}

int	new_fd(char *filename, t_token_type type)
{
	int	fd;

	if (type == REDIR_IN)
	{
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666 | O_TRUNC);
		if (fd == -1)
		{
			write(2, "bash: ", 6);
			perror(filename);
		}
		return (fd);
	}
	if (type == REDIR_ADD)
	{
		fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0666);
		if (fd == -1)
		{
			write(2, "bash: ", 6);
			perror(filename);
		}
		return (fd);
	}
	else if (type == REDIR_OUT)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			write(2, "bash: ", 6);
			perror(filename);
		}
		return (fd);
	}
	return (0);
}

int	set_fd(t_cmds *c_tbls, t_token *token)
{
	if ((*token).type == REDIR_IN || (*token).type == REDIR_ADD)
	{
		c_tbls->out = new_fd(token[1].token, (*token).type);
		if (c_tbls->out < 0)
			return (-2);
		if (c_tbls->file_out)
			free(c_tbls->file_out);
		c_tbls->file_out = ft_strdup(token[1].token);
		if (c_tbls->file_out == NULL)
		{
			perror(NULL);
			return (-1);
		}	
		if (new_fds_list(c_tbls, c_tbls->out) == -1)
			return (-1);
	}
	else
	{
		c_tbls->in = new_fd(token[1].token, (*token).type);
		if (c_tbls->in < 0)
			return (-2);
		if (c_tbls->file_in)
			free(c_tbls->file_in);
		c_tbls->file_in = ft_strdup(token[1].token);
		if (c_tbls->file_in == NULL)
		{
			perror(NULL);
			return (-1);
		}	
		if (new_fds_list(c_tbls, c_tbls->in) == -1)
			return (-1);
	}
	return (0);
}

int	cmds_len(t_cmds *c_tbls, t_token *token)
{
	unsigned int	i;

	i = 0;
	while (token[i].type == STR && token[i].token != NULL)
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
