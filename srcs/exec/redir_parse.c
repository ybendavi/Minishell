/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:08:00 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/29 18:09:19 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_lim(t_token *token, t_cmds *cmd)
{
	char	*buff;

	pipe(cmd->pfd_in);
	buff = readline(">");
	while (ft_strncmp(buff, token[1].token, ft_strlen(token[1].token + 1)) != 0)
	{
		write(cmd->pfd_in[1], buff, ft_strlen(buff));
		write(cmd->pfd_in[1], "\n", 1);
		if (buff)
			free(buff);
		buff = NULL;
		buff = readline(">");
	}
	close(cmd->pfd_in[1]);
	if (buff)
		free(buff);
}

int	redir_set_cmds(t_token *token, t_cmds *tmp)
{
	int	i;

	i = 0;
	if (&token[1] && &token[2])
		i = 1 + set_cmds(tmp, &token[2]);
	return (i);
}

int	redir_parse(t_env *envs, t_token *token)
{
	int		i;
	t_cmds	*tmp;

	tmp = envs->c_tbls;
	i = 0;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	else
	{
		if (new_table(envs) == -1)
			return (-1);
		tmp = envs->c_tbls;
	}
	if ((*token).type != REDIR_LIM)
		i = set_fd(tmp, token);
	else
		redir_lim(token, tmp);
	if (i != 0)
		return (i);
	return (redir_set_cmds(token, tmp));
}

int	is_redir_rec(t_token *tokens)
{
	if ((*tokens).type == REDIR_IN
		|| (*tokens).type == REDIR_OUT
		|| (*tokens).type == REDIR_ADD
		|| (*tokens).type == REDIR_LIM)
		return (1);
	return (0);
}
