/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:21:57 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 21:40:28 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cut_var(char **temp, t_env *data, char *var, int y)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (var[y])
	{
		while (var[y] && !is_ws(var[y]))
			y++;
		str = ft_calloc(y - i + 1);
		if (!str)
			return (-1);
		j = 0;
		while (i < y)
			str[j++] = var[i++];
		if (get_lexed(ft_cpy(temp, str), data, STR))
			return (-1);
		free(str);
		while (is_ws(var[y]))
			y++;
		if (get_lexed(ft_cpy(temp, " "), data, WHITE_SPACE))
			return (-1);
		i = y;
	}
	return (0);
}

int	env_var_2(char **temp, t_env *data, char *str)
{
	unsigned int	y;

	y = 0;
	while (str[y] && str[y] != ' ' && str[y] != '\r' && str[y] != '\t'
		&& str[y] != '\n' && str[y] != '\v' && str[y] != '\f')
		y++;
	if (y == ft_strlen(str))
	{
		if (get_lexed(ft_cpy(temp, str), data, STR))
			return (-1);
	}
	else
	{
		if (cut_var(temp, data, str, 0))
			return (-1);
	}
	return (0);
}

int	env_var(char **temp, t_env *data, char *line, unsigned int *i)
{
	char	*str;
	char	*var;

	var = NULL;
	str = NULL;
	if (find_var_name(line, i, &var))
		return (-1);
	if (ft_getenv(var, &str, data->env))
		return (-1);
	free(var);
	if (!str)
		return (0);
	if (env_var_2(temp, data, str))
	{
		free(str);
		return (-1);
	}
	free(str);
	return (0);
}

int	handle_env(char **temp, t_env *data, unsigned int *i, char *line)
{
	if (check_temp(temp, data))
		return (-1);
	if (ft_isdigit(line[*i + 1]))
		return (digit_var(temp, data, i, line));
	else if (line[*i + 1] == '$')
	{
		(*temp)[0] = '$';
		(*temp)[1] = '$';
		(*i)++;
		return (get_lexed(temp, data, STR));
	}
	else if (line[*i + 1] == '?')
		return (is_status_code(i, temp, data));
	else if (*i != 0 && (line[*i + 1] == '\''
			|| (line[*i - 1] != '"' && line[*i + 1] == '"')))
		return (get_lexed(temp, data, STR));
	else if (*i == 0 && (line[*i + 1] == '"' || line[*i + 1] == '\''))
		return (get_lexed(temp, data, STR));
	else if (is_char_env(line[(*i) + 1]))
		return (env_var(temp, data, line, i));
	return (get_lexed(ft_cpy(temp, "$"), data, STR));
}
