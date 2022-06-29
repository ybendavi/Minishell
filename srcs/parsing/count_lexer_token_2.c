/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lexer_token_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:42:52 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/29 19:35:51 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(char **temp, unsigned int *i, char *line)
{
	int	count;

	count = count_temp(temp);
	if (is_char_env(line[(*i) + 1]))
	{
		(*i)++;
		while (is_char_env(line[*i]))
			(*i)++;
		return (count + 2);
	}
	else if (ft_isdigit(line[*i] + 1))
	{
		*i = *i + 2;
		if (line[*i - 1] == '0')
			return (count + 1);
		else
			return (count);
	}
	return (count + 1);
}

int	count_double(char *line, unsigned int *i, unsigned int start,
		char **temp)
{
	unsigned int	j;
	int				count;

	j = start;
	count = 1;
	while (j < *i)
	{
		while (line[j] == '$')
		{
			if (j != start)
				count++;
			count += count_env(temp, &j, line);
			while (is_char_env(line[++j]))
				add_temp(line, temp, j);
			count += count_temp(temp);
			if (j == *i)
				return (count);
			start = j;
		}
		j++;
	}
	return (count);
}

int	count_quote(char *line, unsigned int *i, char **temp)
{
	unsigned int	start;
	int				count;
	char			q;

	count = count_temp(temp);
	q = line[*i];
	start = *i;
	*i = *i + 1;
	while (line[*i] && line[*i] != q)
		*i = *i + 1;
	if (*i == ft_strlen(line))
		return (-2);
	if (q == '"')
		count += count_double(line, i, start + 1, temp);
	else
		count++;
	return (count);
}
