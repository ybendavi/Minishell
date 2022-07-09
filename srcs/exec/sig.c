/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:48:18 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/09 15:52:55 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

int	check_global(void)
{
	//printf("check_global = %d\n", g_sig);
	if (g_sig == 42)
		return (1);
	else
		return (0);
}

void	handler_child(int sig)
{
	if (sig == SIGINT)
	{
	//	printf("handler_child in\n");
		g_sig = 42;
		close(0);
		close(1);
		close(2);
	}
}

void	exit_int(t_env *envs, char **buff, int fd)
{
	if (g_sig == 42)
	{
		if (fd > 0)
		{
			dup2(fd, 0);
			close(fd);
		}
		if (buff)
		{
			if (*buff)
				free(*buff);
		}
	//	printf("exit_int = %d\n", g_sig);
		free_exec(envs);
		exit(1);
	}
}

void	kill_int(int sig)
{
	//printf("kill_int = %d\n", g_sig);
	if (sig == SIGINT)
		g_sig = 42;
}

int	sig_back(t_env *envs, int status_code)
{
/*	sigemptyset(&(envs->sig_q.sa_mask));
	sigaddset(&(envs->sig_q.sa_mask), SIGQUIT);
	envs->sig_q.sa_handler = SIG_IGN;
	envs->sig_q.sa_flags = 0;
	sigaction(SIGQUIT, &(envs->sig_q), NULL);
	sigemptyset(&(envs->sig_i.sa_mask));
	sigaddset(&(envs->sig_i.sa_mask), SIGINT);
	envs->sig_i.sa_handler = &handler_sig;
	envs->sig_i.sa_flags = 0;
	sigaction(SIGINT, &(envs->sig_i), NULL);*/
	if (g_sig == 42)
		status_code = 130;
	close_fds(envs->c_tbls);
	return (status_code);
}
