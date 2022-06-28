/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:12:05 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/28 13:43:31 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *data, char **strs)
{
	int	i;

	if (!strs)
		return (0);
	if (strs[1])
	{
		write(2, "env: ", 5);
		write(2, strs[1], ft_strlen(strs[1]));
		write(2, ": No argument required\n", 23);
		return (1);
	}
	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
