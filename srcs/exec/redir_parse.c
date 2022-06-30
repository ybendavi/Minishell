/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:08:00 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/30 18:20:38 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_process(t_token *token, t_cmds *cmd, t_env *envs)
{
	char	*buff;

	(void) envs;
	close(cmd->pfd_in[0]);
	buff = readline(">");	
	while (ft_strncmp(buff, token[1].token, ft_strlen(token[1].token + 1)) != 0)
	{
		write(cmd->pfd_in[1], buff, ft_strlen(buff));
		write(cmd->pfd_in[1], "\n", 1);
		if (buff)
			free(buff);
		buff = NULL;
		buff = readline(">");
		if (!buff)
		{
			write(1, "warning: here-document delimited by ", 36);
			write(1, "end-of-file (wanted `file')\n", 29);
			exit (0);
		}
	}
	close(cmd->pfd_in[1]);
	if (buff)
		free(buff);
	exit (0);
}

void	redir_lim(t_token *token, t_cmds *cmd, t_env *envs)
{
	pid_t	forking;
	int	status;

	pipe(cmd->pfd_in);
	forking = fork();
	if (forking < 0)
		return ;
	if (forking == 0)
		redir_process(token, cmd, envs);
	else if (forking > 0)
	{
		close(cmd->pfd_in[1]);
		wait(&status);
	}
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
		redir_lim(token, tmp, envs);
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
