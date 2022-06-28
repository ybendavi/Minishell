/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:44:25 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/28 18:10:35 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **strs)
{
	char	mark;
	int	i;
	int	ret;

	if (!strs)
		return (0);
	mark = 0;
	i = 1;
	while (!(ft_strncmp(strs[i], "-n", 2)))
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
