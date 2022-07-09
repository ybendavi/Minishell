/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:27:38 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/09 14:20:27 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_null_table(t_cmds **tmp)
{
	(*tmp)->file_in = NULL;
	(*tmp)->file_out = NULL;
	(*tmp)->cmds = NULL;
	(*tmp)->cmd = NULL;
	(*tmp)->path = NULL;
	(*tmp)->in = 0;
	(*tmp)->out = 1;
	(*tmp)->next = NULL;
	(*tmp)->delim = NULL;
	(*tmp)->lim = malloc(sizeof(int) * 2);
	(*tmp)->pfd_in = malloc(sizeof(int) * 2);
	(*tmp)->pfd_out = malloc(sizeof(int) * 2);
	(*tmp)->fork = -10;
}

int	test_table(t_env *envs, t_cmds *tmp)
{
	if (!tmp->pfd_in)
		return (-1);
	if (!tmp->pfd_out)
		return (-1);
	if (!tmp->lim)
		return (-1);
	tmp->lim[0] = -1;
	tmp->pfd_in[0] = -1;
	tmp->pfd_out[0] = -1;
	tmp->pfd_in[1] = -1;
	tmp->lim[1] = -1;
	tmp->pfd_out[1] = -1;
	if (!envs->c_tbls || !tmp)
		return (-1);
	return (0);
}

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
	set_null_table(&tmp);
	return (test_table(envs, tmp));
}
