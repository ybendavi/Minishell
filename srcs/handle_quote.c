/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:10:03 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/07 18:15:38 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_quote(char **temp, char *line, unsigned int i, unsigned int start)
{
	int	y;

	y = 0;
	while (start <= i)
	{
		(*temp)[y] = line[start];
		y++;
		start++;
	}
	return (temp);
}

int	handle_double(char *line, unsigned int *i, unsigned int start,
		t_env *data)
{
	unsigned int	j;

	j = start;
	while (j < *i)
	{
		while (line[j] == '$')
		{
			if (j != start)
			{
				if (get_lexed(copy_quote(data->temp, line,
					j - 1, start), data, STR))
					return (-1);
			}
			if (get_lexed(ft_cpy(data->temp, "$"), data, ENV))
				return (-1);
			while (is_char_env(line[++j]))
				add_temp(line, data->temp, j);
			if (check_temp(data->temp, data))
				return (-1);
			if (j == *i)
				return (0);
			start = j;
		}
		j++;
	}
	return (get_lexed(copy_quote(data->temp, line, j - 1, start), data, STR));
}

int	handle_quote(char *line, unsigned int *i, char **temp, t_env *data)
{
	unsigned int		start;
	char	q;

	if (check_temp(temp, data))
		return (-1);
	q = line[*i];
	start = *i;
	*i = *i + 1;
	while (line[*i] && line[*i] != q)
		*i = *i + 1;
	if (*i == ft_strlen(line))
		return (-2);
	if (q == '"')
	{
		data->temp = temp;
		if (handle_double(line, i, start + 1, data))
			return (-1);
	}
	else
	{
		if (get_lexed(copy_quote(temp, line, *i - 1, start + 1), data, STR))
			return (-1);
	}
	return (0);
}
