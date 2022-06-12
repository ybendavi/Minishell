/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:49:03 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/07 20:54:04 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_parsed(t_env *data, t_token token)
{
	if (token.type == WHITE_SPACE)
		return (0);
	else
		data->parsed[data->nb_parsed].token = ft_cpy2(token.token);
	if (!data->parsed[data->nb_parsed].token)
		return (-1);
	data->parsed[data->nb_parsed].size = token.size;//
	data->parsed[data->nb_parsed].type = token.type;
	data->nb_parsed++;
	return (0);
}

int	is_redir(unsigned int i, t_env *data)
{
	if (i == 0)
	{
		if (get_parsed(data, data->lexed[i]))
			return (-1);
	}
	else if (data->parsed[data->nb_parsed - 1].type != PIPE
		&& data->parsed[data->nb_parsed - 1].type != STR
		&& data->parsed[data->nb_parsed - 1].type != ENV)
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

int	check_type(unsigned int *i, t_env *data, char **env)
{
	if (data->lexed[*i].type == WHITE_SPACE)
		return (is_whitespace(i, data));
	if (data->lexed[*i].type == REDIR_ADD
		|| data->lexed[*i].type == REDIR_LIM
		|| data->lexed[*i].type == REDIR_IN 
		|| data->lexed[*i].type == REDIR_OUT)
		return (is_redir(*i, data));
	else if (data->lexed[*i].type == PIPE)
		return (is_pipe(*i, data));
	else if (data->lexed[*i].type == ENV)
		return (is_env(i, data, env));
	else if (data->lexed[*i].type == STR)
		return (is_str(i, data));
	return (0);
}

void	add_null_token(t_env *data)
{
	t_token	token;

	token.token = NULL;
	token.type = STR;
	token.size = 0;
	data->parsed[data->nb_parsed] = token;
	data->nb_parsed++;
}

int	init_parser(t_env *data, char **env)
{
	unsigned int	i;
	int	ret;

	i = 0;
	data->parsed = ft_calloc(100 * sizeof(t_token));//dynamique
	if (!data->parsed)
		return (-1);
	while (i < data->nb_token)
	{
		ret = check_type(&i, data, env);
		if (ret)
		{
			data->error = data->lexed[i].token;
			return (ret);
		}
		i++;
	}
	add_null_token(data);
	free_lexed(data);
	return (0);
}
