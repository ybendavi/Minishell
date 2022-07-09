/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lexer_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:39:24 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/09 17:04:35 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_temp(char **temp)
{
	int	i;

	if (ft_strlen(*temp) != 0)
	{
		i = 0;
		while ((*temp)[i])
		{
			(*temp)[i] = 0;
			i++;
		}
		return (1);
	}
	return (0);
}

int	count_redir(char *line, unsigned int *i, char **temp)
{
	int		count;
	char	r;

	count = count_temp(temp);
	r = line[*i];
	if (line[*i + 1] == r)
	{
		*i = *i + 1;
		count++;
	}
	else
		count++;
	return (count);
}

int	count_pipe(char **temp)
{
	int	count;

	count = count_temp(temp);
	count++;
	return (count);
}

int	count_white_space(unsigned int *i, char *line, char **temp)
{
	unsigned int	start;
	int				count;

	count = count_temp(temp);
	start = *i;
	while (line[*i] == ' ' || line[*i] == '\r' || line[*i] == '\t'
		|| line[*i] == '\n' || line[*i] == '\v' || line[*i] == '\f')
		*i = *i + 1;
	if (start != *i)
		count++;
	*i = *i - 1;
	return (count);
}

int	count_lexer_token(char *line, char **temp, t_env *data, unsigned int i)
{
	int	ret;
	int	count;

	count = 0;
	while (line[i])
	{
		ret = 0;
		if (line[i] == '|')
			ret = count_pipe(temp);
		else if (line[i] == '>' || line[i] == '<')
			ret = count_redir(line, &i, temp);
		else if (line[i] == '\'' || line[i] == '"')
			ret = count_quote(line, &i, temp);
		else if (line[i] == ' ' || line[i] == '\r' || line[i] == '\t'
			|| line[i] == '\n' || line[i] == '\v' || line[i] == '\f')
			ret = count_white_space(&i, line, temp);
		else if (line[i] == '$')
			ret = count_env(temp, line, &i, data);
		else
			add_temp(line, temp, i);
		if (ret < 0)
			return (ret);
		count += ret;
		i++;
	}
	count += count_temp(temp);
	return (count);
}
