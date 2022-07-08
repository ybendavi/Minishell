/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:48:18 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/08 15:00:44 by ybendavi         ###   ########.fr       */
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
	envs->sig_i.sa_handler = &handler_sig;
	sigaction(SIGINT, &(envs->sig_i), NULL);
	if (g_sig == 42)
		status_code = 130;
	close_fds(envs->c_tbls);
	return (status_code);
}
