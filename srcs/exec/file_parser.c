/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:32:34 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/10 21:36:30 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fd_out(t_cmds *c_tbls, t_token *token)
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
	return (0);
}

int	redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(2, "bash: ", 6);
		perror(filename);
	}
	return (fd);
}
