/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:09:58 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/06 17:50:41 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_w_export(t_env *data)
{
	int		i;
	char	**strs;

	i = 0;
	while (data->env[i])
	{
		strs = ft_split(data->env[i], '=');
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

int	not_valid(char *str)
{
	write(2, "bash: export: `", 16);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}
