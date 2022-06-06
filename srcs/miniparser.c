/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:32:13 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/06 20:10:47 by ybendavi         ###   ########.fr       */
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

int	redir_parse(t_env *envs, char **strs)
{
	int		i;
	t_cmds	*tmp;

	i = 0;
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
	set_fd(tmp, strs);
	i = 1 + set_cmds(tmp, &strs[2]);
	return (i);
}

int	pipe_parse(t_env *envs, char **strs)
{
	t_cmds	*tmp;
	int		i;

	i = 0;
	tmp = envs->c_tbls;
	while (tmp->next)
		tmp = tmp->next;
	new_table(envs);
	if (pipe(tmp->pfd_out) == -1)
	{
		perror(NULL);
		return (-1);
	}
	tmp->out = tmp->pfd_out[1];
	tmp->next->pfd_in[0] = tmp->pfd_out[0];
	tmp->next->pfd_in[1] = tmp->pfd_out[1];
	tmp->next->in = tmp->next->pfd_in[0];
	tmp = tmp->next;
	i = set_cmds(tmp, &strs[1]);
	return (i);
}

int	recu_parse(t_env *envs, char **strs)
{
	int	i;

	if (ft_strncmp(">", *strs, ft_strlen(*strs)) == 0
		|| ft_strncmp("<", *strs, ft_strlen(*strs)) == 0
		|| ft_strncmp(">>", *strs, ft_strlen(*strs)) == 0
		|| ft_strncmp("<<", *strs, ft_strlen(*strs)) == 0)
	{
		i = redir_parse(envs, strs);
		if (i == -1)
			return (-1);
		if (strs[i] && strs[i + 1])
		{
			if (recu_parse(envs, &strs[i + 1]) == -1)
				return (-1);
		}
	}
	if (ft_strncmp("|", *strs, ft_strlen(*strs)) == 0)
	{
		i = pipe_parse(envs, strs);
		if (i == -1)
			return (-1);
		if (strs[i] && strs[i + 1])
		{
			if (recu_parse(envs, &strs[i + 1]) == -1)
				return (-1);
		}
	}
	return (0);
}

int	parsing(t_env *envs, char *av)
{
	int		i;
	char	**strs;

	strs = ft_split(av, ' ');
	envs->c_tbls = NULL;
	i = 0;
	if (choose_tok(*strs) == 0)
	{
		new_table(envs);
		i = set_cmds(envs->c_tbls, strs);
	}
	if (strs[i] && recu_parse(envs, &strs[i]) == -1)
		return (-1);
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}
