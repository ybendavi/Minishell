/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:42:26 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/07 22:14:53 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	struct_env(char *str, int type)
{
	t_token	token;

	token.token = str;
	token.type = type;
	return (token);
}

int	get_env_var(char **env, char **var)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i] && ft_env_strnstr(env[i], *var, ft_strlen(*var)) == NULL)
		i++;
	if (env[i] == NULL)
	{
		i = 0;
		while ((*var)[i])
		{
			(*var)[i] = 0;
			i++;
		}
		return (0);
	}
	str = ft_strchr(env[i], '=');
	i = 0;
	while ((*var)[i])
	{
		(*var)[i] = 0;
		i++;
	}
	ft_cpy(var, &str[1]);
	return (0);
}
