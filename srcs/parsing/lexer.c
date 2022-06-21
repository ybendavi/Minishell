/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:24:47 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/06 21:01:25 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_lexer(t_env *data, char **temp, char *line)
{
	data->nb_token = 0;
	data->lexed = ft_calloc(sizeof(t_token) * 100);//DYMANIQUE
	if (!data->lexed)
		return (-1);
	*temp = ft_calloc(ft_strlen(line) + 2);
	if (!temp)
		return (-1);
	return (0);
}

int	get_lexed(char **temp, t_env *data, t_token_type type)
{
	int	y;

	data->lexed[data->nb_token].size = ft_strlen(*temp);
	data->lexed[data->nb_token].type = type;
	data->lexed[data->nb_token].token
		= ft_calloc(data->lexed[data->nb_token].size + 1);
	if (!data->lexed[data->nb_token].token)
		return (-1);
	y = 0;
	while ((*temp)[y])
	{
		data->lexed[data->nb_token].token[y] = (*temp)[y];
		(*temp)[y] = 0;
		y++;
	}
	data->nb_token++;
	return (0);
}

void	add_temp(char *line, char **temp, unsigned int i)
{
	int	y;

	y = 0;
	while ((*temp)[y])
		y++;
	(*temp)[y] = line[i];
}

int	lexer2(char *line, char **temp, unsigned int *i, t_env *data)
{
	if (line[*i] == '|')
		return (handle_pipe(temp, data));
	else if (line[*i] == '>' || line[*i] == '<')
		return (handle_redir(line, i, temp, data));
	else if (line[*i] == '\'' || line[*i] == '"')
		return (handle_quote(line, i, temp, data));
	else if (line[*i] == ' ' || line[*i] == '\r' || line[*i] == '\t'
		|| line[*i] == '\n' || line[*i] == '\v' || line[*i] == '\f')
		return (handle_white_space(i, line, temp, data));
	else if (line[*i] == '$')
		return (handle_env(temp, data, i, line));
	else
		add_temp(line, temp, *i);
	return (0);
}

int	lexer(char *line, t_env *data)
{
	char	*temp;
	unsigned int		i;
	int		ret;

	if (ft_cmp(line, "") == 1)
		return (0);
	if (init_lexer(data, &temp, line) == -1)
		return (-1);
	i = 0;
	ret = 0;
	while (line[i])
	{
		ret = lexer2(line, &temp, &i, data);
		if (ret < 0)
		{
			free(temp);
			return (ret);
		}
		i++;
	}
	if (ft_strlen(temp) != 0)
		get_lexed(&temp, data, STR);
	free(temp);
	return (0);
}
