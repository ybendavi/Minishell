/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:40:02 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/26 15:45:13 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*praise_neg_max(int n)
{
	int		i;
	char	*ret;

	ret = ft_calloc(12);
	if (!ret)
		return (NULL);
	ret[10] = '8';
	ret[0] = '-';
	i = 9;
	n = n * -1;
	while (i > 0)
	{
		ret[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (ret);
}

static int	get_len(int n)
{
	int	i;

	i = 0;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	int		mark;
	int		y;
	char	*ret;

	mark = 0;
	if (n == -2147483648)
		return (praise_neg_max(n / 10));
	if (n < 0)
	{
		n = -1 * n;
		mark = 1;
	}
	y = get_len(n) + mark;
	ret = ft_calloc(y + 1);
	if (!ret)
		return (NULL);
	if (mark == 1)
		ret[0] = '-';
	while (n > 9)
	{
		ret[--y] = (n % 10) + 48;
		n = n / 10;
	}
	ret[--y] = n + 48;
	return (ret);
}
