/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:10:03 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 15:49:09 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_quotes(char **temp, t_env *data, char *line, unsigned int *i)
{
	char	*str;
	char	*var;

	var = NULL;
	str = NULL;
	if (find_var_name(line, i, &var))
		return (-1);
	if (ft_getenv(var, &str, data->env))
		return (-1);
	free(var);
	if (!str)
		return (0);
	if (get_lexed(ft_cpy(temp, str), data, STR))
		return (-1);
	return (0);
}

int	handle_env_quotes(char **temp, t_env *data, unsigned int *i, char *line)
{
	if (check_temp(temp, data))
		return (-1);
	if (ft_isdigit(line[*i + 1]))
		return (digit_var(temp, data, i, line));
	else if (line[*i + 1] == '?')
		return (is_status_code(i, temp, data));
	else if (line[*i + 1] == '$')
	{
		(*temp)[0] = '$';
		(*temp)[1] = '$';
		(*i)++;
		return (get_lexed(temp, data, STR));
	}
	else if (*i != 0 && (line[*i + 1] == '\''
			|| (line[*i - 1] != '"' && line[*i + 1] == '"')))
		return (get_lexed(temp, data, STR));
	else if (*i == 0 && (line[*i + 1] == '"' || line[*i + 1] == '\''))
		return (get_lexed(temp, data, STR));
	else if (is_char_env(line[(*i) + 1]))
		return (env_var_quotes(temp, data, line, i));
	return (get_lexed(ft_cpy(temp, "$"), data, STR));
}

char	**copy_quote(char **temp, char *line, unsigned int i,
		unsigned int start)
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
	unsigned int	y;

	y = 0;
	while (start < *i)
	{
		if (line[start] == '$')
		{
			if (y)
			{	
				if (get_lexed(data->temp, data, STR))
					return (-1);
				y = 0;
			}
			if (handle_env_quotes(data->temp, data, &start, line))
				return (-1);
			if (start == *i)
				return (0);
		}
		else
			(*data->temp)[y++] = line[start];
		start++;
	}
	return (get_lexed(data->temp, data, STR));
}

int	handle_quote(char *line, unsigned int *i, char **temp, t_env *data)
{
	unsigned int	start;
	char			q;

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
		{
			if (handle_double(line, i, start + 1, data))
				return (-1);
		}
	}
	else
	{
		if (get_lexed(copy_quote(temp, line, *i - 1, start + 1), data, STR))
			return (-1);
	}
	return (0);
}
