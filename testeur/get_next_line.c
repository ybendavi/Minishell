/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <ybendavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:42:31 by ybendavi          #+#    #+#             */
/*   Updated: 2021/03/24 11:21:37 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*s1;

	i = 0;
	s1 = s;
	while (i < n)
	{
		s1[i] = 0;
		i++;
	}
}

char	*line_set(char *buffer, char *str)
{
	char	*ptr;

	free(buffer);
	if (ft_strchr(str, '\n') != NULL)
	{
		ptr = str;
		ft_strchr(str, '\n')[0] = 0;
		str = ft_strdup(str);
		free(ptr);
	}
	return (str);
}

char	*saved(char *str, char *rst)
{
	int	i;

	i = 0;
	if (rst != NULL)
	{
		while (rst != NULL && rst[i])
		{
			str[i] = rst[i];
			i++;
		}
	}
	if (rst != NULL)
		free(rst);
	return (str);
}

int		return_conditions(char *buffer, char *str, int res, char **line)
{
	if (res == -1)
	{
		free(buffer);
		free(str);
		return (res);
	}
	if (ft_strchr(str, '\n') != NULL && ft_strchr(str, '\n')[1] != 0)
		res = 1;
	(*line) = line_set(buffer, str);
	if (res == -1 || res == 0)
		return (res);
	else
		return (1);
}

int		get_next_line(int fd, char **line)
{
	char		*str;
	char		*buffer;
	int			res;
	static char	*rst;

	if (line == NULL || fd < 0)
		return (-1);
	res = 3;
	if (!(buffer = ft_calloc(BUFFER_SIZE + 1, 1)))
		return (-1);
	if (!(str = ft_calloc(ft_strlen(rst) + 1, 1)))
		return (-1);
	str = saved(str, rst);
	rst = NULL;
	while (res != 0 && res != -1 && ft_strchr(str, '\n') == NULL)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		str = ft_strjoin_free(str, buffer);
		ft_bzero(buffer, res + 1);
	}
	if (ft_strchr(str, '\n') != NULL)
		rst = ft_strdup(&ft_strchr(str, '\n')[1]);
	return (return_conditions(buffer, str, res, line));
}
