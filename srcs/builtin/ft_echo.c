/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:44:25 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 13:07:01 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_compflag(char *str)
{
	unsigned int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

int	ft_echo(char **strs)
{
	char	mark;
	int		i;
	int		ret;

	if (!strs)
		return (0);
	mark = 0;
	i = 1;
	while (strs[i] && ft_compflag(strs[i]))
	{
		mark = 1;
		i++;
	}
	while (strs[i])
	{
		ret = write(1, strs[i], ft_strlen(strs[i]));
		if (strs[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!mark)
		write(1, "\n", 1);
	return (0);
}
