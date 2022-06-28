/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:58:50 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/28 14:30:39 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_w_export(t_env *data)
{
	int	i;
	char	**strs;

	i = 0;
	while (data->env[i])
	{
		strs=ft_split(data->env[i], '=');
		if (!strs)
			return (-1);
		if (strs[1] == NULL)
			strs[1] = ft_strdup("");
		printf("export %s=\"%s\"\n", strs[0], strs[1]);
		free(strs[0]);
		free(strs[1]);
		free(strs);
		i++;
	}
	return (0);
}

int	is_good_str(char *str)
{
	int	i;

	i = 0;
	if (!is_char_env(str[i]))
		return (0);
	i++;
	while (str[i] && is_str_env(str[i]))
		i++;
	if (str[i] == '=' && i != 0)
		return (1);
	else if (str[i] == 0)
		return (2);
	else
		return (0);
}

void	not_valid(char *str)
{
	write(2, "bash: export: `", 16);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
}

int	realloc_env(t_env *data)
{
	int	i;
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

	y = 0;
	while (data->env[y])
		y++;
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
	while (env[y][i] && str[i] && env[y][i] != '=' && str[i] != '=')
	{
		if (env[y][i] != str[i])
			return (0);
		i++;
	}
	if (env[y][i] == 0 || str[i] == 0)
		return (0);
	if (env[y][i] != str[i])
		return (0);
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
	if (count == 0)
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
		{
			mark = 1;
			not_valid(strs[i]);
		}
		i++;
	}	
	return (mark);
}
