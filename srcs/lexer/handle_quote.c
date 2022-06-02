/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:10:03 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/02 23:10:28 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_quote(char **temp, char *line, int i, int start)
{
	int	y;

	y = 0;
	while (start <= i)
	{
		(*temp)[y] = line[start];
		y++;
		start++;
	}
}

void	count_q(char *line, int *i, int *nb_q, char q)
{
	while (line[*i] == q)
	{
		*i = *i + 1;
		*nb_q = *nb_q + 1;
	}
}

int	handle_quote(char *line, int *i, char **temp, t_env *env)
{
	int		start;
	int		nb_q;
	char	q;

	if (check_temp(temp, env))
		return (-1);
	q = line[*i];
	start = *i;
	nb_q = 0;
	count_q(line, i, &nb_q, q);
	while (line[*i] && line[*i] != q)
		*i = *i + 1;
	count_q(line, i, &nb_q, q);
	if (nb_q % 2 == 0)
	{
		copy_quote(temp, line, *i, start);
		if (get_lexed(temp, env, STR))
			return (-1);
		return (0);
	}
	return (-2);
}

