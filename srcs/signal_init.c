/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:51:36 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/07 14:53:04 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sig(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
	{
		if (g_sig == 0)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			write(1, "\nminishell$ \r", 14);
		}
	}
}

int	signal_init(t_env *data)
{
	struct sigaction	sig_q;
	struct sigaction	sig_i;
	int					ret;

	sig_i.sa_sigaction = &handler_sig;
	sigemptyset(&(sig_i.sa_mask));
	sigaddset(&(sig_i.sa_mask), SIGINT);
	sig_i.sa_flags = SA_SIGINFO;
	sigemptyset(&(sig_q.sa_mask));
	sigaddset(&(sig_q.sa_mask), SIGQUIT);
	sig_q.sa_handler = SIG_IGN;
	sig_q.sa_flags = 0;
	ret = sigaction(SIGINT, &sig_i, NULL);
	ret = sigaction(SIGQUIT, &sig_q, NULL);
	data->sig_q = sig_q;
	data->sig_i = sig_i;
	if (ret)
		return (ret);
	return (0);
}
