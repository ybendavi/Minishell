/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:21:56 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/26 18:09:54 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	else if (data->lexed[*i + 1].token[0] == '?')(voir avec chef comment stocker ca et ou et garder si c simple quote)
int	get_env_var(char **env, char **var)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i] && ft_env_strnstr(env[i], *var, ft_strlen(*var)) == NULL)
		i++;
	if (env[i] == NULL)
	{
		if (*var)
			free(*var);
		*var = NULL;
		return (0);
	}
	str = ft_strchr(env[i], '=');
	if (*var)
		free(*var);
	if (ft_mcpy(&str[1], var))
		return (-1);
	return (0);
}

t_token	struct_env(char *str, int type)
{
	t_token	token;

	token.token = str;
	token.type = type;
	return (token);
}

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
		data->parsed[data->nb_parsed - 1].token =
		ft_concat(data->parsed[data->nb_parsed - 1].token, *str);
		if (!data->parsed[data->nb_parsed - 1].token)
			return (-1);
		data->parsed[data->nb_parsed - 1].size
		= ft_strlen(data->parsed[data->nb_parsed - 1].token);
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

int	is_env(unsigned int *i, t_env *data, char **env)
{
	char	*str;
	unsigned int	y;
	
	str = NULL;
	y = *i;
	while (data->lexed[y].type == ENV)
	{
		if (y + 1 < data->nb_token
		&& is_char_env(data->lexed[y + 1].token[0]))
		{
			y++;
			if (get_env_var(env, &(data->lexed[y].token)))
				return (-1);
			if (data->lexed[y].token)
			{
				str = ft_concat(str, data->lexed[y].token);
				if (!str)
					return (-1);
			}
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
