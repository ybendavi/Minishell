/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:44:25 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/25 21:03:59 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **strs)
{
	char	mark;
	int	i;
	int	ret;

	mark = 0;
	if (ft_cmp(strs[1], "-n"))
		mark = 1;
	i = 1 + mark;
	while (strs[i])
	{
		ret = write(1, strs[i], ft_strlen(strs[i]));
		if (ret)
			return (ret);//? + rajouter un espace entre chaqu
		i++;
	}
	if (mark)
		write(1, "\n", 1);
	return (0);
}
