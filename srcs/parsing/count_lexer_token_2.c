/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lexer_token_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:42:52 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/07 21:17:38 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(char **temp)
{
	int	count;

	count = count_temp(temp);
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
			count += count_env(temp);
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
	if (q == '"')
		count += count_double(line, i, start + 1, temp);
	else
		count++;
	return (count);
}
