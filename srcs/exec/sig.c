/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:48:18 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/10 19:27:02 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

int	check_global(void)
{
	if (g_sig == 42)
		return (1);
	else
		return (0);
}

void	handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 42;
		close(0);
		close(1);
		close(2);
	}
}

void	exit_int(t_env *envs, char **buff)
{
	if (g_sig == 42)
	{
		if (buff)
		{
			if (*buff)
				free(*buff);
		}
		free_exec(envs);
		exit(1);
	}
}

void	kill_int(int sig)
{
	if (sig == SIGINT)
		g_sig = 42;
}

int	sig_back(t_env *envs, int status_code)
{
	t_cmds	*tmp;

	tmp = envs->c_tbls;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp->status != 0)
		status_code = tmp->status;
	if (g_sig == 42)
		status_code = 130;
	close_fds(envs->c_tbls);
	return (status_code);
}
