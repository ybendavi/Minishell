/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:09:58 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/06 18:29:38 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_w_export(t_env *data)
{
	char	**strs;
	int		i;
	int		y;

	i = 0;
	while (data->env[i])
	{
		strs = ft_split(data->env[i], '=');
		if (!strs)
			return (-1);
		if (strs[1] == NULL)
			strs[1] = ft_strdup("");
		if (strs[0] && strs[1])
			printf("export %s=\"%s\"\n", strs[0], strs[1]);
		y = 0;
		while (strs[y])
		{
			if (strs[y])
				free(strs[y]);
			y++;
		}
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
	if ((str[i] == '=' || (str[i] == '+' && str[i + 1] == '=')) && i != 0)
		return (1);
	else if (str[i] == 0)
		return (2);
	else
		return (0);
}

int	not_valid(char *str)
{
	write(2, "bash: export: `", 16);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

int	handle_add(t_env *data, char *str, int plus)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(str));
	if (!new)
		return (-1);
	i = 0;
	j = 0;
	while (str[j])
	{
		if (j == plus)
			j++;
		new[i] = str[j];
		i++;
		j++;
	}
	while (data->env[i])
		i++;
	data->env[i] = new;
	return (0);
}

int	add_to_var(char **env, char *str, int y)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	i = ft_strlen(str) - j;
	new = ft_calloc(ft_strlen(env[y]) + i + 1);
	if (!new)
		return (-1);
	i = 0;
	while (env[y][i])
	{
		new[i] = env[y][i];
		i++;
	}
	j++;
	while (str[j])
		new[i++] = str[j++];
	free(env[y]);
	env[y] = new;
	return (1);
}
