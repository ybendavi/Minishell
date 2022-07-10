/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:36:41 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 23:26:22 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_of_env(char *line, unsigned int *i, t_env *data)
{
	char	*str;
	char	*var;
	int		y;

	var = NULL;
	str = NULL;
	if (find_var_name(line, i, &var))
		return (-1);
	if (ft_getenv(var, &str, data->env))
		return (-1);
	free(var);
	if (!str)
		return (0);
	y = 0;
	while (str[y])
		y++;
	free(str);
	return (y);
}

int	count_size_temp(char *line, t_env *data)
{
	unsigned int	i;
	int				ret;
	int				count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			ret = size_of_env(line, &i, data);
			if (ret == -1)
				return (ret);
			count += ret;
		}
		i++;
	}
	count += i;
	return (count);
}

int	ultimate_good_char(char c)
{
	if ((c > 32 && c < 127) && c != '<'
		&& c != '>' && c != '|' && c != '\'' && c != '"')
		return (1);
	return (0);
}
