/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lexer_token_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:42:52 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/09 17:30:17 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_env(char *line, unsigned int *i, t_env *data, int count)
{
	char	*str;
	char	*var;
	int		y;

	var = NULL;
	str = NULL;
	if (find_var_name(line, i, &var))
		return (-1);
	if (ft_getenv(var, &str, data->env))
		return (-1);
	if (var)
		free(var);
	if (!str)
		return (0);
	y = 0;
	while (str[y])
	{
		y++;
		if (str[y] == ' ' || str[y] == '\r' || str[y] == '\t'
		|| str[y] == '\n' || str[y] == '\v' || str[y] == '\f')
			count++;
	}
	free(str);
	return (count);
}

int	count_env(char **temp, char *line, unsigned int *i, t_env *data)
{
	int	count;
	int	tmp;

	count = count_temp(temp);
	tmp = size_env(line, i, data, 0);
	if (tmp == -1)
		return (-1);
	count += (tmp * 2) + 1;
	return (count);
}

int	count_double(char *line, unsigned int *i, unsigned int start)
{
	unsigned int	j;
	int				count;

	j = start;
	count = 1;
	while (j < *i)
	{
		if (line[j] == '$')
			count++;
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
		count += count_double(line, i, start + 1);
	else
		count++;
	return (count);
}
