/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:58:50 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/28 17:16:33 by ybendavi         ###   ########.fr       */
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
		return (1);
	i++;
	while (str[i] && is_str_env(str[i]))
		i++;
	if (str[i] == '=' && i != 0)
		return (0);
	else if (str[i] == 0)
		return (2);
	else
		return (1);
}

int	not_valid(char *str)
{
	write(2, "bash: export: `", 16);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

int	realloc_env(t_env *data, int add)
{
	int	i;
	char	**new;

	i = 0;
	while (data->env[i])
		i++;
	new = ft_calloc(sizeof(char *) * (i + add + 1));
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

int	fill_new_env(t_env *data, char **strs)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
	while (data->env[y])
		y++;
	while (strs[i])
	{
		data->env[y] = ft_strdup(strs[i]);
		if (!data->env[y])
			return (-1);
		y++;
		i++;
	}
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

int	check_already_exist(char **env, char **strs)
{
	int	i;
	int	y;
	int	count;
	int	ret;

	i = 1;
	count = 0;
	while (strs[i])
	{
		y = 0;
		while (env[y])
		{
			ret = cmp_var_env(env, strs[i], y);
			if (ret == -1)
				return (-1);
			count += ret; 
			y++;
		}
		i++;
	}
	return (count);
}

int	ft_export(char **strs, t_env *data)
{
	int	i;
	int	ret;

	i = 1;
	if (!strs[i])
		return (print_env_w_export(data));
	while (strs[i])
	{
		ret = is_good_str(strs[i]);
		if (ret == 2)
			return (0);
		if (ret == 1)
			return (not_valid(strs[i]));
		i++;
	}
	ret = check_already_exist(data->env, strs);
	if (ret == -1)
		return (-1);
	i -= ret;
	if (i == 1)
		return (0);
	if (realloc_env(data, i - 1))
		return (-1);
	if (fill_new_env(data, strs))
		return (-1);
	return (0);
}

