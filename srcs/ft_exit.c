/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:26:46 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/26 12:19:33 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

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

int	ft_get_status(char *str)
{
	int	ret;
	int	i;
	char	mark;

	i = 0;
	mark = 1;
	if ((str[i] == '-' || str[i] == '+') && (str[i + 1] >= 48 && str[i + 1] <= 67))
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
		exit(2);
	}
	return (ft_mini_atoi(str) * mark);
}

void	ft_exit(t_env *data, char **strs)
{
	int	nb;

	nb = 0;
	if (strs[1])
		nb = ft_get_status(strs[1]);	
	free_parsed(data);
	free_lexed(data);
	freeer(data);
	free_all(data);
	write(1, "exit\n", 5);
	exit(nb);
}
