/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:20:24 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/27 19:58:55 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

char	*ft_env_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;
	size_t	n;
	char	*ret;

	ret = (char *)big;
	if (ft_strlen(little) == 0)
		return (ret);
	i = 0;
	while (big[i] && i < len)
	{
		y = 0;
		n = i;
		while (n < len && big[n] == little[y])
		{
			n++;
			y++;
			if (little[y] == '\0' && big[n] == '=')
				return (ret);
		}
		ret++;
		i++;
	}
	return (0);
}

char	*ft_cpy2(char *s1)
{
	char	*s2;
	int	i;

	i = 0;
	s2 = ft_calloc(ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

int	ft_mcpy(char *s1, char **s2)
{
	int	i;

	i = 0;
	*s2 = ft_calloc(ft_strlen(s1) + 1);
	if (!*s2)
		return (-1);
	while (s1[i])
	{
		(*s2)[i] = s1[i];
		i++;
	}
	return (0);
}

int	ft_cmp(char *s1, char *s2)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	if (ft_strlen(s1) == i && ft_strlen(s2) == i)
		return (1);
	return (0);
}
