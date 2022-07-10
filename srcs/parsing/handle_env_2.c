/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:14:00 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 15:26:13 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	digit_var(char **temp, t_env *data, unsigned int *i, char *line)
{
	(*i)++;
	if (line[*i] == '0')
		return (get_lexed(ft_cpy(temp, "bash"), data, STR));
	return (0);
}

int	is_status_code(unsigned int *i, char **temp, t_env *data)
{
	char	*str;

	(*i)++;
	str = ft_itoa(data->status_code);
	if (!str)
		return (-1);
	ft_cpy(temp, str);
	free(str);
	return (get_lexed(temp, data, STR));
}

int	find_var_name(char *line, unsigned int *i, char **var)
{
	unsigned int	y;

	if (!is_char_env(line[(*i) + 1]))
		return (0);
	(*i)++;
	y = *i;
	while (is_str_env(line[y]))
		y++;
	*var = ft_calloc(y - *i + 1);
	if (!*var)
		return (-1);
	y = 0;
	while (is_str_env(line[*i]))
	{
		(*var)[y] = line[*i];
		y++;
		(*i)++;
	}
	(*i)--;
	return (0);
}

int	ft_getenv(char *var, char **str, char **env)
{
	char	*temp;
	int		i;

	i = 0;
	if (!var || !env)
		return (0);
	while (env[i] && ft_env_strnstr(env[i], var, ft_strlen(var)) == NULL)
		i++;
	if (env[i] == NULL)
		return (0);
	temp = ft_strchr(env[i], '=');
	if (ft_mcpy(&temp[1], str))
		return (-1);
	return (0);
}
