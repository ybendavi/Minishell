/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:21:56 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/29 22:25:20 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_status_code(t_env *data, char **str)
{
	char	*s;

	s = ft_itoa(data->status_code);
	if (!s)
		return (-1);
	*str = ft_concat(*str, s);
	if (!*str)
		return (-1);
	free(s);
	return (0);
}

int	add_to_prev_token(t_env *data, char **str)
{
	data->parsed[data->nb_parsed - 1].token
		= ft_concat(data->parsed[data->nb_parsed - 1].token, *str);
	if (!data->parsed[data->nb_parsed - 1].token)
		return (-1);
	data->parsed[data->nb_parsed - 1].size
		= ft_strlen(data->parsed[data->nb_parsed - 1].token);
	return (0);
}

int	parse_env(unsigned int *i, t_env *data, int y, char **str)
{
	if (!*str)
		return (0);
	while (data->lexed[y].type == STR)
	{
		*str = ft_concat(*str, data->lexed[y].token);
		if (!*str)
			return (-1);
		y++;
	}
	if (data->nb_parsed > 0 && data->lexed[*i - 1].type != WHITE_SPACE)
	{
		if (add_to_prev_token(data, str))
			return (-1);
	}
	else
	{
		if (get_parsed(data, struct_env(*str, STR)))
			return (-1);
	}
	*i = y - 1;
	free(*str);
	return (0);
}

int	is_env_2(t_env *data, char **str, unsigned int y)
{
	if (get_env_var(data->env, &(data->lexed[y].token)))
		return (-1);
	if (data->lexed[y].token)
	{
		*str = ft_concat(*str, data->lexed[y].token);
		if (!*str)
			return (-1);
	}
	return (0);
}

int	is_env(unsigned int *i, t_env *data, char *str)
{
	unsigned int	y;

	y = *i;
	while (data->lexed[y].type == ENV)
	{
		if (y + 1 < data->nb_token
			&& is_char_env(data->lexed[y + 1].token[0]))
		{
			y++;
			if (is_env_2(data, &str, y))
				return (-1);
		}
		else if (data->lexed[y].token && data->lexed[y].token[1] == '?')
		{
			if (is_status_code(data, &str))
				return (-1);
		}
		y++;
	}
	return (parse_env(i, data, y, &str));
}
