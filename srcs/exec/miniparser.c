/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:32:13 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/25 14:06:04 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_table(t_env *envs)
{
	t_cmds	*tmp;

	tmp = envs->c_tbls;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_cmds) * 1);
		if (!tmp->next)
			return (-1);
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	else
	{
		tmp = malloc(sizeof(t_cmds) * 1);
		if (!tmp)
			return (-1);
		tmp->prev = NULL;
		envs->c_tbls = tmp;
	}
	tmp->file_in = NULL;
	tmp->file_out = NULL;
	tmp->cmds = NULL;
	tmp->cmd = NULL;
	tmp->path =NULL;
	tmp->in = 0;
	tmp->out = 1;
	tmp->next = NULL;
	tmp->pfd_in = malloc(sizeof(int) * 2);
	tmp->pfd_out = malloc(sizeof(int) * 2);
 
	if (!tmp->pfd_in)
		return (-1);
	if (!tmp->pfd_out)
		return (-1);
	tmp->pfd_in[0] = -1;
	tmp->pfd_out[0] = -1;
	tmp->pfd_in[1] = -1;
	tmp->pfd_out[1] = -1;
	if (!envs->c_tbls || !tmp)
		return (-1);
	return (0);
}

int	redir_parse(t_env *envs, t_token *token)
{
	int		i;
	t_cmds	*tmp;

	tmp = envs->c_tbls;
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
	i = set_fd(tmp, token);
	if (i != 0)
		return (i);
	i = 0;
	i = 1 + set_cmds(tmp, &token[1]);
	return (i);
}

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
	if ((*tokens).type == REDIR_IN
		|| (*tokens).type == REDIR_OUT
		|| (*tokens).type == REDIR_ADD
		|| (*tokens).type == REDIR_LIM)
	{
		i = redir_parse(envs, tokens);
		if (i == -1 || i == -2 || i == -3)
			return (i);
		if (tokens[i].token != NULL && tokens[i + 1].token != NULL)
		{
			if (recu_parse(envs, &tokens[i + 1]))
				return (-1);
		}
	}
	if ((*tokens).type == PIPE)
	{
		i = pipe_parse(envs, tokens);
		if (i == -1 || i == -2 || i == -3)
			return (i);
		if (tokens[i].token != NULL && tokens[i + 1].token != NULL)
		{
			if (recu_parse(envs, &tokens[i + 1]) == -1)
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
