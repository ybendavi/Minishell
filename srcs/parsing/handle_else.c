/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_else.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:13:31 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/26 16:27:38 by ccottin          ###   ########.fr       */
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

int	env_var(char **temp, t_env *data, unsigned int *i, char *line)
{
	int	ret;
	
	ret = get_lexed(ft_cpy(temp, "$"), data, ENV);
	if (ret)
		return (ret);
	while (is_str_env(line[++(*i)]))
		add_temp(line, temp, *i);
	(*i)--;
	return (get_lexed(temp, data, ENV));
}

int	digit_var(char **temp, t_env *data, unsigned int *i, char *line)
{
	(*i)++;
	if (line[*i] == '0')
		return (get_lexed(ft_cpy(temp, "bash"), data, STR));
	else
		return (get_lexed(temp, data, STR));
}

int	handle_env(char **temp, t_env *data, unsigned int *i, char *line)
{
	if (check_temp(temp, data))
		return (-1);
	if (is_char_env(line[(*i) + 1]))
		return (env_var(temp, data, i, line));
	else if (ft_isdigit(line[*i + 1]))
		return (digit_var(temp, data, i, line));
	else if (line[*i + 1] == '$')
	{
		(*temp)[0] = '$';
		(*temp)[1] = '$';
		(*i)++;
		return (get_lexed(temp, data, STR));
	}
	else if (line[*i + 1] == '?')
	{
		(*temp)[0] = '$';
		(*temp)[1] = '?';
		(*i)++;
		return (get_lexed(temp, data, ENV));
	}
	else if (line[*i + 1] == '"' || line[*i + 1] == '\'')
		return (get_lexed(temp, data, STR));
	return (get_lexed(ft_cpy(temp, "$"), data, STR));
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
		if (get_lexed(ft_cpy(temp, "<"), data, REDIR_IN))
			return (-1);
	}
	return (0);
}

//si on en abesoin, ici rajouter une decoupe des whitespace char par char un peu comme le tableau de token
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
