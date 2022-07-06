/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:08:00 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/06 21:21:55 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_lim(t_token *token, t_cmds *cmd)
{
	cmd->delim = ft_strdup(token[1].token);
	if (!cmd->delim)
		return (-1);
	pipe(cmd->lim);
	return (0);
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
		i = redir_lim(token, tmp);
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
