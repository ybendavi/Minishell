/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:34:36 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/29 16:34:38 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_main(t_env *envs)
{
	int	i;

	i = 0;
	if (envs->env)
	{
		while (envs->env[i] && ft_strnstr(envs->env[i], "PWD=", 4) == NULL)
			i++;
		if (ft_strnstr(envs->env[i], "PWD=", 4) != NULL)
			printf("%s\n", &ft_strchr(envs->env[i], '=')[1]);
	}
	return (0);
}