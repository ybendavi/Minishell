/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 23:00:42 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/28 00:02:50 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_existing_var(char *str, char **env)
{
	int	unsigned i;
	int	y;

	i = 0;
	if (!is_char_env(str[i]))
		return (-1);
	i++;
	while (str[i] && is_str_env(str[i]))
		i++;
	if (i != ft_strlen(str))
		return (-1);
	i = 0;
	y = 0;
	while (env[y])
	{
		while (env[y][i] == str[i])
			i++;
		if (i == ft_strlen(str) && env[y][i] == '=')
			return (y);
		y++;
	}
	return (0);
}

int	delete_var(t_env *data, int line)
{
	char	**new;
	int		i;
	int		y;

	i = 0;
	while (data->env[i])
		i++;
	new = ft_calloc(sizeof(char *) * i);
	if (!new)
		return (-1);
	i = 0;
	y = 0;
	while (data->env[i])
	{
		if (i != line)
		{
			new[y] = ft_strdup(data->env[i]);
			if (!new[y])
				return (-1);
		}
		i++;
		y++;
	}
	free_env(data);
	data->env = new;
	return (0);
}

void	not_valid_2(char *str)
{
	write(2, "bash: unset: `", 14);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);

}

int	ft_unset(char **strs, t_env *data)
{
	int	i;
	int	mark;
	int	ret;

	mark = 0;
	i = 1;
	if (!strs[1])
		return (0);
	while (strs[i])
	{
		ret = is_existing_var(strs[i], data->env);
		if (ret < 0)
		{
			not_valid_2(strs[i]);
			mark = 1;
		}
		else if (ret > 0)
		{
			if (delete_var(data, ret))
				return (-1);
		}
		i++;	
	}
	return (mark);
}
