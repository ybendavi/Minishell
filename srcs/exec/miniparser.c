/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:32:13 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/09 19:46:02 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_parse(t_env *envs, t_token *token)
{
	t_cmds	*tmp;
	int		i;

	i = 0;
	tmp = envs->c_tbls;
	while (tmp->next)
		tmp = tmp->next;
	if (new_table(envs) == -1)
		return (-1);
	if (pipe(tmp->pfd_out) == -1)
	{
		perror(NULL);
		return (-3);
	}
	tmp->out = tmp->pfd_out[1];
	tmp->next->pfd_in[0] = tmp->pfd_out[0];
	tmp->next->pfd_in[1] = tmp->pfd_out[1];
	tmp->next->in = tmp->next->pfd_in[0];
	tmp = tmp->next;
	i = set_cmds(tmp, &token[1]);
	return (i);
}

int	recu_parse(t_env *envs, t_token *tokens)
{
	int	i;

	if ((*tokens).token == NULL)
		return (0);
	if (is_redir_rec(tokens) || (*tokens).type == PIPE)
	{
		if (is_redir_rec(tokens))
			i = redir_parse(envs, tokens);
		else
			i = pipe_parse(envs, tokens);
		if (i == -1 || i == -2 || i == -3)
			return (i);
		if (tokens[i].token != NULL && tokens[i + 1].token != NULL)
		{
			if (recu_parse(envs, &tokens[i + 1]))
				return (-1);
		}
	}
	return (0);
}

int	parsing(t_env *envs)
{
	int	i;
	int	ret;

	i = 0;
	envs->c_tbls = NULL;
	if ((*envs->parsed).type == STR)
	{
		new_table(envs);
		i = set_cmds(envs->c_tbls, envs->parsed);
	}
	ret = recu_parse(envs, &envs->parsed[i]);
	if (ret != 0)
		return (-1);
	free_parsed(envs);
	return (0);
}
