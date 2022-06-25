/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:51:36 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/25 18:37:01 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sig(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGINT)
		write(1, "\n", 1);
//	if (sig == SIGQUIT)
		
}

int	signal_init(void)
{
	struct sigaction	sig;
	int	ret;

	sig.sa_sigaction = &handler_sig;
	sigemptyset(&(sig.sa_mask));
	sigaddset(&(sig.sa_mask), SIGQUIT);
	sigaddset(&(sig.sa_mask), SIGINT);
	sig.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGINT, &sig, NULL);
	ret = sigaction(SIGQUIT, &sig, NULL);
	if (ret)	
		return (ret);
	return (0);
}
