/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:49:03 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/28 17:25:57 by ccottin          ###   ########.fr       */
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
	data->parsed[data->nb_parsed].size =
		ft_strlen(data->parsed[data->nb_parsed].token);
	data->parsed[data->nb_parsed].type = token.type;
	data->nb_parsed++;
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
	int	count;
	int	ret;

	i = 0;
	count = count_parser_token(data);
	if (count < 0)
		return (count);
	printf("nb parsed = %d\n", count);
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
	printf("nb really parsed = %d\n", data->nb_parsed);
	ret = check_parsing_errors(data);
	if (ret)
		return (ret);
	return (0);
}
