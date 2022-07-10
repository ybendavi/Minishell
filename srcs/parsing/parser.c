/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 12:23:06 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 18:00:06 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(unsigned int i, t_env *data)
{
	if (i == 0)
		return (-3);
	if (data->nb_parsed > 0
		&& data->parsed[data->nb_parsed - 1].type != STR)
		return (-3);
	else
	{
		if (get_parsed(data, data->lexed[i]))
			return (-1);
	}
	return (0);
}

char	*ft_concat(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		y;

	if (!s1)
		ret = ft_calloc(ft_strlen(s2) + 1);
	else
		ret = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
	}
	y = 0;
	while (s2 && s2[y])
		ret[i++] = s2[y++];
	if (s1)
		free(s1);
	return (ret);
}

int	is_str(unsigned int *i, t_env *data)
{
	t_token	token;

	token.token = NULL;
	while (data->lexed[*i].type == STR)
	{
		if (!data->lexed[*i].token)
			return (0);
		token.token = ft_concat(token.token, data->lexed[*i].token);
		if (!token.token)
			return (-1);
		*i = *i + 1;
	}
	*i = *i - 1;
	token.type = STR;
	if (get_parsed(data, token))
	{
		free(token.token);
		return (-1);
	}
	free(token.token);
	return (0);
}

int	is_redir(unsigned int i, t_env *data)
{
	if (i == 0)
	{
		if (get_parsed(data, data->lexed[i]))
			return (-1);
	}
	else if (data->nb_parsed > 0
		&& data->parsed[data->nb_parsed - 1].type != PIPE
		&& data->parsed[data->nb_parsed - 1].type != STR)
		return (-3);
	else
	{
		if (get_parsed(data, data->lexed[i]))
			return (-1);
	}
	return (0);
}

int	is_whitespace(unsigned int *i, t_env *data)
{
	while (data->lexed[*i].type == WHITE_SPACE)
		*i = *i + 1;
	*i = *i - 1;
	if (get_parsed(data, data->lexed[*i]))
		return (-1);
	return (0);
}
