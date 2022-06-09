/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:07:36 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/06 17:04:43 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_temp(char **temp, t_env *data)
{
	if (ft_strlen(*temp) != 0)
	{
		if (get_lexed(temp, data, STR))
			return (-1);
	}
	return (0);
}

char	**ft_cpy(char **temp, char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		(*temp)[i] = s1[i];
		i++;
	}
	return (temp);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmem)
{
	char	*ret;
	size_t	i;

	ret = malloc(nmem);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nmem)
	{
		ret[i] = 0;
		i++;
	}
	return ((void *)ret);
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

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	c1;
	char	*s1;

	s1 = (char *)s;
	c1 = (char)c;
	i = 0;
	while (i < (ft_strlen(s) + 1))
	{
		if (s1[i] == c1)
			return (&s1[i]);
		i++;
	}
	return (NULL);
}
