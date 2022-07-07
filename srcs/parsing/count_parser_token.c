/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_parser_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:50:11 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/07 21:11:45 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	c_str(t_token *token, unsigned int *i)
{
	while (token[*i].type == STR)
		(*i)++;
	(*i)--;
	return (1);
}

int	count_type(unsigned int *i, t_env *data)
{
	if (data->lexed[*i].type == WHITE_SPACE)
		return (0);
	if (data->lexed[*i].type == REDIR_ADD
		|| data->lexed[*i].type == REDIR_LIM
		|| data->lexed[*i].type == REDIR_IN
		|| data->lexed[*i].type == REDIR_OUT)
		return (1);
	else if (data->lexed[*i].type == PIPE)
	{
		if (*i == 0)
			return (-3);
		return (1);
	}
	else if (data->lexed[*i].type == STR)
		return (c_str(data->lexed, i));
	return (0);
}

int	count_parser_token(t_env *data)
{
	int				count;
	int				ret;
	unsigned int	i;

	i = 0;
	count = 0;
	while (i < data->nb_token)
	{
		ret = count_type(&i, data);
		if (ret < 0)
		{
			data->error = data->lexed[i].token;
			return (ret);
		}
		count += ret;
		i++;
	}
	count++;
	return (count);
}
