/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:29 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/29 18:46:00 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_env *data)
{
	unsigned int	i;

	i = 0;
	while (i < 12)
	{
		if (data->tab[i].token)
			free(data->tab[i].token);
		i++;
	}
	if (data->tab)
		free(data->tab);
	free_env(data);
}
