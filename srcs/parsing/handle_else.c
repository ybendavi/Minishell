/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_else.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:13:31 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 19:15:58 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe(char **temp, t_env *data)
{
	if (check_temp(temp, data))
		return (-1);
	if (get_lexed(ft_cpy(temp, "|"), data, PIPE))
		return (-1);
	return (0);
}

int	parse_lim_token(char **temp, t_env *data, char *line, unsigned int *i)
{
	unsigned int	j;
	char	c;

	j = *i;
	if (line[*i] && (line[*i] == '"' || line[*i] == '\''))
	{
		c = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != c)
			(*i)++;
		if (*i == ft_strlen(line) && line[*i] != c)
			return (-2);

		return (get_lexed(copy_quote(temp, line, *i - 1,
				*i - (*i - j) + 1), data, STR));
	}
	while (line[*i] && (line[*i] > 32 && line[*i] < 127))
	{
		add_temp(line, temp, *i);
		(*i)++;
	}
	return (get_lexed(temp, data, STR));
}

int	is_double_redir(char **temp, t_env *data, char *line, unsigned int *i)
{
	if (line[*i] && line[*i] == '>')
	{
		if (get_lexed(ft_cpy(temp, ">>"), data, REDIR_ADD))
			return (-1);
	}
	if (line[*i] && line[*i] == '<')
	{
		if (get_lexed(ft_cpy(temp, "<<"), data, REDIR_LIM))
			return (-1);
		(*i)++;
		while (line[*i] && is_ws(line[*i]))
		{
			if (get_lexed(ft_cpy(temp, " "), data, WHITE_SPACE))
				return (-1);
			(*i)++;
		}
		if (line[*i] && (line[*i] == '|'
			|| line[*i] == '<' || line[*i] == '>'))
		{
			(*i)--;
			return (0);
		}
		return (parse_lim_token(temp, data, line, i));
	}
	return (1);
}

int	handle_redir(char *line, unsigned int *i, char **temp, t_env *data)
{
	char	r;

	if (check_temp(temp, data))
		return (-1);
	r = line[*i];
	if (line[*i + 1] == r)
	{
		*i = *i + 1;
		return (is_double_redir(temp, data, line, i));
	}
	else if (line[*i] == '>')
	{
		if (get_lexed(ft_cpy(temp, ">"), data, REDIR_IN))
			return (-1);
	}
	else if (line[*i] == '<')
	{
		if (get_lexed(ft_cpy(temp, "<"), data, REDIR_OUT))
			return (-1);
	}
	return (0);
}

int	handle_white_space(unsigned int *i, char *line, char **temp,
		t_env *data)
{
	unsigned int	start;

	if (check_temp(temp, data))
		return (-1);
	start = *i;
	while (line[*i] == ' ' || line[*i] == '\r' || line[*i] == '\t'
		|| line[*i] == '\n' || line[*i] == '\v' || line[*i] == '\f')
		*i = *i + 1;
	if (start != *i)
	{
		if (get_lexed(ft_cpy(temp, " "), data, WHITE_SPACE))
			return (-1);
	}
	*i = *i - 1;
	return (0);
}
