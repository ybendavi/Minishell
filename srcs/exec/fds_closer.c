/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_closer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:24:05 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/09 15:19:19 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds_two(t_cmds *tmp)
{
	if (tmp->lim[0] != -1 && tmp->lim[0] != -3)
	{
		close(tmp->lim[0]);
		tmp->lim[0] = -3;
	}
	if (tmp->lim[1] != -1 && tmp->lim[1] != -3)
	{
		close(tmp->lim[1]);
		tmp->lim[1] = -3;
	}
	if (tmp->pfd_in[0] != -1 && tmp->pfd_in[0] != -3)
	{
		close(tmp->pfd_in[0]);
		tmp->pfd_in[0] = -3;
	}
	if (tmp->pfd_in[1] != -1 && tmp->pfd_in[1] != -3)
	{
		close(tmp->pfd_in[1]);
		tmp->pfd_in[1] = -3;
	}
	if (tmp->pfd_out[0] != -1 && tmp->pfd_out[0] != -3)
	{
		close(tmp->pfd_out[0]);
		tmp->pfd_out[0] = -3;
	}
	if (tmp->pfd_out[1] != -1 && tmp->pfd_out[1] != -3)
	{
		close(tmp->pfd_out[1]);
		tmp->pfd_out[1] = -3;
	}
}

int	close_fds(t_cmds *cmd)
{
	t_cmds	*tmp;

	tmp = cmd;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->in != 0 && tmp->in != -1 && tmp->in != -3)
		{
			close(tmp->in);
			tmp->in = -3;
		}
		if (tmp->out != 1 && tmp->out != -1 && tmp->out != -3)
		{
			close(tmp->out);
			tmp->out = -3;
		}
		close_fds_two(tmp);
		tmp = tmp->next;
	}
	return (0);
}
