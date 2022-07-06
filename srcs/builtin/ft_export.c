/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:58:50 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/06 18:29:19 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	realloc_env(t_env *data)
{
	int		i;
	char	**new;

	i = 0;
	while (data->env[i])
		i++;
	new = ft_calloc(sizeof(char *) * (i + 2));
	if (!new)
		return (-1);
	i = 0;
	while (data->env[i])
	{
		new[i] = ft_strdup(data->env[i]);
		if (!new[i])
			return (-1);
		i++;
	}
	free_env(data);
	data->env = new;
	return (0);
}

int	fill_new_env(t_env *data, char *str)
{
	int	y;
	int	i;

	y = 0;
	while (data->env[y])
		y++;
	i = 0;
	while (str[i] && (str[i] != '+' && str[i] != '='))
		i++;
	if (str[i] == '+')
		return (handle_add(data, str, i));
	data->env[y] = ft_strdup(str);
	if (!data->env[y])
		return (-1);
	y++;
	return (0);
}

int	cmp_var_env(char **env, char *str, int y)
{
	int	i;

	i = 0;
	while (env[y][i] && str[i] && env[y][i] != '='
		&& (str[i] != '=' || str[i] != '+'))
	{
		if (env[y][i] != str[i])
			return (0);
		i++;
	}
	if (env[y][i] == 0 || str[i] == 0)
		return (0);
	if (env[y][i] == '=' && (str[i] != '=' && str[i] != '+'))
		return (0);
	if (str[i] == '+' && env[y])
		return (add_to_var(env, str, y));
	else if (str[i] == '+')
		return (2);
	free(env[y]);
	env[y] = ft_strdup(str);
	if (!env[y])
		return (-1);
	return (1);
}

int	check_already_exist(char **env, char *str, t_env *data)
{
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (env[y] && count == 0)
	{
		count = cmp_var_env(env, str, y);
		if (count == -1)
			return (-1);
		y++;
	}
	if (count == 0 || count == 2)
	{
		if (realloc_env(data))
			return (-1);
		if (fill_new_env(data, str))
			return (-1);
	}
	return (0);
}

int	ft_export(char **strs, t_env *data)
{
	int	i;
	int	mark;
	int	ret;

	if (!strs)
		return (0);
	i = 1;
	if (!strs[i])
		return (print_env_w_export(data));
	mark = 0;
	while (strs[i])
	{
		ret = is_good_str(strs[i]);
		if (ret == 1)
		{
			if (check_already_exist(data->env, strs[i], data))
				return (-1);
		}
		else if (ret == 0)
			mark = not_valid(strs[i]);
		i++;
	}	
	return (mark);
}
