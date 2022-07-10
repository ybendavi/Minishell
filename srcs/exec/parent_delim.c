/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_delim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:02:25 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/10 20:36:37 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delim_parent(t_cmds *cmds, int status, t_env *envs)
{
	(void) envs;
	if (cmds->lim[0] != -1 && cmds->lim[0] != -3)
	{
		close(cmds->lim[0]);
		cmds->lim[0] = -3;
	}
	if (cmds->lim[1] != -1 && cmds->lim[1] != -3)
	{
		close(cmds->lim[1]);
		cmds->lim[1] = -3;
	}
	waitpid(cmds->fork, &status, 0);
	if (WIFEXITED(status) != 0)
		cmds->status = WEXITSTATUS(status);
	if (check_global() == 1)
		return (1);
	return (0);
}

int	parent_process(t_cmds *cmds, int status, t_env *envs)
{
	if (cmds->in != 0 && cmds->in != -1 && cmds->in != -3)
	{
		close(cmds->in);
		cmds->in = -3;
	}
	if (cmds->prev && cmds->prev->out != 1 && cmds->prev->out != -1
		&& cmds->prev->out != -3)
	{
		close(cmds->prev->out);
		cmds->prev->out = -3;
	}
	if (cmds->delim)
	{
		if (delim_parent(cmds, status, envs) == 1)
			return (1);
	}
	return (0);
}
