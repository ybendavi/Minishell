/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:39:42 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/29 16:43:57 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_no_args(t_env *envs)
{
	int		i;
	char	*cupath;

	i = 0;
	cupath = NULL;
	if (envs->env)
	{
		while (envs->env[i] && ft_strnstr(envs->env[i], "HOME=", 5) == NULL)
			i++;
		if (ft_strnstr(envs->env[i], "HOME=", 5) != NULL)
		{
			cupath = ft_strdup(&(ft_strchr(envs->env[i], '=')[1]));
			if (chdir(cupath) == -1)
				perror(envs->cupath);
			if (cupath)
				free(cupath);
		}
		else
		{
			write(2, "bash: cd: HOME not set\n",
				ft_strlen("bash: cd: HOME not set\n"));
			return (1);
		}
	}
	return (0);
}

int	cd_other_case(char **av, t_env *envs, int i)
{	
	if (i == 1)
		return (ft_cd_no_args(envs));
	if (i == 2)
	{
		if (chdir(av[1]) == -1)
		{
			perror(av[1]);
			return (1);
		}
		return (0);
	}
	return (0);
}

int	cd_main(char **av, t_env *envs)
{
	int	i;

	i = 0;
	if (av)
	{
		while (av[i])
			i++;
		if (i > 2)
		{
			write(2, "bash: cd: too many arguments\n",
				ft_strlen("bash: cd: too many arguments\n"));
			return (1);
		}
		else
			return (cd_other_case(av, envs, i));
	}
	return (0);
}
