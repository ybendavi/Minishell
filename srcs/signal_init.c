/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:23:01 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/22 19:17:31 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sig(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	(void) sig;
	printf("coucou");
	exit(0);
}

int	signal_init(void)
{
	struct sigaction	sig;
	int	ret;

	sig.sa_sigaction = &handler_sig;
	if (sigemptyset(&(sig.sa_mask)) == -1)
		printf("erreur\n");
	sigaddset(&(sig.sa_mask), SIGINT);
	sig.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGINT, &sig, NULL);
	if (ret)	
		return (ret);
	return (0);
}
