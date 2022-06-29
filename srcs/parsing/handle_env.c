/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:39:48 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/29 17:40:22 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (0);
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
