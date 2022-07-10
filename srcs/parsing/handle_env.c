/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:21:57 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 14:47:48 by ybendavi         ###   ########.fr       */
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

int	cut_var(char **temp, t_env *data, char *var, int y)
{
	char	*str;
	int		i;
	int		j;

	i = y - 1;
	while (var[y])
	{
		while (var[y] && (var[y] != ' ' && var[y] != '\r' && var[y] != '\t'
			&& var[y] != '\n' && var[y] != '\v' && var[y] != '\f'))
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
		while (var[y] == ' ' || var[y] == '\r' || var[y] == '\t'
			|| var[y] == '\n' || var[y] == '\v' || var[y] == '\f')
			y++;
		if (get_lexed(ft_cpy(temp, " "), data, WHITE_SPACE))
			return (-1);
		i = y;
	}
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

int	env_var(char **temp, t_env *data, char *line, unsigned int *i)
{
	char	*str;
	char	*var;
	unsigned int		y;

	var = NULL;
	str = NULL;
	if (find_var_name(line, i, &var))
		return (-1);
	if (ft_getenv(var, &str, data->env))
		return (-1);
	free(var);
	if (!str)
		return (0);
	y = 0;
	while(str[y] && str[y] != ' ' && str[y] != '\r' && str[y] != '\t'
		&& str[y] != '\n' && str[y] != '\v' && str[y] != '\f')
		y++;
	if (y == ft_strlen(str))
	{
		if (get_lexed(ft_cpy(temp, str), data, STR))
		{
			free(str);
			return (-1);
		}
	}
	else
	{	
		if (cut_var(temp, data, str, y))
		{
			free(str);
			return (-1);
		}
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
