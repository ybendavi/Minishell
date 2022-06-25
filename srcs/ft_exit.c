/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:26:46 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/25 19:44:05 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_env *data)
{
	free_parsed(data);
	free_lexed(data);
	freeer(data);
	free_all(data);
	write(1, "exit\n", 5);
	exit(0);
}
