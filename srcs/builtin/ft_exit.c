/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:26:46 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/30 20:37:07 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mini_atoi(char *str)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		ret = ret * 10 + (str[i] - 48);
		i++;
	}
	return (ret);
}

int	ft_get_status(char *str, t_env *data)
{
	unsigned int			i;
	char					mark;

	i = 0;
	mark = 1;
	if ((str[i] == '-' || str[i] == '+')
		&& (str[i + 1] >= 48 && str[i + 1] <= 67))
	{
		if (str[i] == '-')
			mark = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 67)
		i++;
	if (i != ft_strlen(str))
	{
		write(2, "bash: exit: ", 13);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 29);
		free_all_env(data);
		exit(2);
	}
	return (ft_mini_atoi(str) * mark);
}

int	too_many(void)
{
	write(2, "bash: exit: too many arguments\n", 32);
	return (127);
}

int	ft_exit(t_env *data, char **strs)
{
	int	nb;

	if (!strs)
		return (0);
	nb = 0;
	if (strs)
	{
		if (strs[1])
			nb = ft_get_status(strs[1], data);
	}
	if (strs[1] && strs[2])
		return (too_many());
	write(1, "exit\n", 5);
	free_all_env(data);
	exit(nb);
	return (0);
}
