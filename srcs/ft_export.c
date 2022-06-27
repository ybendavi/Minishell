/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:58:50 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/27 19:42:33 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_env_w_export(t_env *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("export %s\n", data->env[i]);
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
	if (str[i] == '=')
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
	new = ft_calloc((sizeof(char *) * i + add + 1));
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
	data->env = new;
	free_env(data);	
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
	if (realloc_env(data, i - 1))
		return (-1);
	if (fill_new_env(data, strs))
		return (-1);
	return (0);
}

int	env_init(t_env *data, char **env);

int	main(int ac, char **av, char **env)
{
	t_env *data;

	env_init(data, env);
	ft_export(av, data);
}
