/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_else.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:13:31 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/29 17:40:17 by ccottin          ###   ########.fr       */
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

int	is_double_redir(char r, char **temp, t_env *data)
{
	if (r == '>')
	{
		if (get_lexed(ft_cpy(temp, ">>"), data, REDIR_ADD))
			return (-1);
	}
	if (r == '<')
	{
		if (get_lexed(ft_cpy(temp, "<<"), data, REDIR_LIM))
			return (-1);
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
		return (is_double_redir(line[*i], temp, data));
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
