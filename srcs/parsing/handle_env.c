/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:39:48 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/07 22:03:37 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_to_prev_token(t_env *data, char **str)
{
	int	i;

	data->lexed[data->nb_token - 1].token
		= ft_concat(data->lexed[data->nb_token - 1].token, *str);
	if (!data->lexed[data->nb_token - 1].token)
		return (-1);
	data->lexed[data->nb_token - 1].size
		= ft_strlen(data->lexed[data->nb_token - 1].token);
	i = 0;
	while ((*str)[i])
	{
		(*str)[i] = 0;
		i++;
	}
	return (0);
}

int	env_var(char **temp, t_env *data, unsigned int *i, char *line)
{
	int	y;

	while (line[*i] == '$')
	{
		(*i)++;
		y = 0;
		while (is_str_env(line[*i]))
		{
			(*temp)[y] = line[*i];
			y++;
			(*i)++;
		}
		if (get_env_var(data->env, temp))
			return (-1);
		if (data->nb_token > 0 && data->lexed[data->nb_token].type == STR)
		{
			if (add_to_prev_token(data, temp))
				return (-1);
		}
		else if (!ft_cmp(*temp, ""))
			get_lexed(temp, data, STR);
	}
	(*i)--;
	return (0);
}

int	digit_var(char **temp, t_env *data, unsigned int *i, char *line)
{
	(*i)++;
	if (line[*i] == '0')
		return (get_lexed(ft_cpy(temp, "bash"), data, STR));
	return (0);
}

int	is_status_code(unsigned int *i, char **temp, t_env *data)
{
	char	*str;

	(*i)++;
	str = ft_itoa(data->status_code);
	if (!str)
		return (-1);
	ft_cpy(temp, str);
	free(str);
	return (get_lexed(temp, data, STR));
}

int	handle_env(char **temp, t_env *data, unsigned int *i, char *line)
{
	if (check_temp(temp, data))
		return (-1);
	if (ft_isdigit(line[*i + 1]))
		return (digit_var(temp, data, i, line));
	else if (line[*i + 1] == '$')
	{
		(*temp)[0] = '$';
		(*temp)[1] = '$';
		(*i)++;
		return (get_lexed(temp, data, STR));
	}
	else if (line[*i + 1] == '?')
		return (is_status_code(i, temp, data));
	else if (*i != 0 && (line[*i + 1] == '\''
		|| (line[*i - 1] != '"' && line[*i + 1] == '"')))
		return (get_lexed(temp, data, STR));
	else if (is_char_env(line[(*i) + 1]))
		return (env_var(temp, data, i, line));	
	return (get_lexed(ft_cpy(temp, "$"), data, STR));
}
