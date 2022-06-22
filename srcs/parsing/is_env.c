/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:05:07 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/21 18:05:41 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	else if (data->lexed[*i + 1].token[0] == '?')(voir avec chef comment stocker ca et ou et garder si c simple quote)

t_token	struct_env(char *str, int type)
{
	t_token	token;

	token.token = str;
	token.type = type;
	return (token);
}

int	parse_env(t_env *data, unsigned int *i, char *str, int y)
{
	if (data->nb_parsed > 0 && data->lexed[*i - 1].type == STR)
	{
		if (str)
		{
			data->parsed[data->nb_parsed - 1].token =
			ft_concat(data->parsed[data->nb_parsed - 1].token, str);
			if (!data->parsed[data->nb_parsed - 1].token)
				return (-1);
			data->parsed[data->nb_parsed - 1].size
			= ft_strlen(data->parsed[data->nb_parsed - 1].token);
		}
		else
			return (get_parsed(data, struct_env("", STR)));
	}
	else if (str && (data->lexed[y].type == WHITE_SPACE || !ft_cmp(str, "")))
			return (get_parsed(data, struct_env(str, STR)));
	return (0);
}

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

int	is_env(unsigned int *i, t_env *data, char **env)
{
	unsigned int	y;
	char	*str;
	
	y = *i;
	str = NULL;
	while (data->lexed[y].type == ENV)
	{
		if (data->nb_token <= y + 1)
		{
			str = ft_concat(str, "$");
			if (!str)
				return (-1);
			y++; //??
		}
		else if (data->lexed[y].token[1] == '"'
			|| data->lexed[y].token[1] == '\'')
		{
			str = ft_concat(str, data->lexed[y + 1].token);
			if (!str)
				return (-1);
		}
		else if (is_char_env(data->lexed[y].token[1]))
		{
			if (get_env_var(env, &(data->lexed[y + 1].token)))
				return (-1);
			if (data->lexed[y + 1].token)
			{
				str = ft_concat(str, data->lexed[y + 1].token);
				if (!str)
					return (-1);
			}
		}
		else
		{
			if (data->lexed[y + 1].type != STR && data->lexed[y + 1].type != ENV)
			{
				str = ft_concat(str, "$");
				if (!str)
					return (-1);
				str = ft_concat(str, data->lexed[y + 1].token);
				if (!str)
					return (-1);
			}
			if (data->lexed[y + 1].type == ENV)
			{
				str = ft_concat(str, "$$");
				if (!str)
					return (-1);
			}

		}
		y = y + 2;
	}
	if (parse_env(data, i, str, y))
		return (-1);
	*i = y - 1;
	if (str)
		free(str);
	return (0);
}
