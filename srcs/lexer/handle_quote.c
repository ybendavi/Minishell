/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:10:03 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/07 18:15:38 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_quote(char **temp, char *line, int i, int start)
{
	int	y;

	y = 0;
	while (start <= i)
	{
		(*temp)[y] = line[start];
		y++;
		start++;
	}
	return (temp);
}

void	count_q(char *line, int *i, int *nb_q, char q)
{
	*nb_q = 0;
	while (line[*i] == q && line[*i])
	{
		*i = *i + 1;
		*nb_q = *nb_q + 1;
	}
}

void	count_q2(char *line, int *i, int *nb_q2, int nb_q1)
{
	char	q;

	*nb_q2 = 0;
	q = line[*i];
	while (line[*i] == q && line[*i] && *nb_q2 < nb_q1)
	{
		*i = *i + 1;
		*nb_q2 = *nb_q2 + 1;
	}
}

int	handle_quote(char *line, int *i, char **temp, t_env *data)
{
	int		start;
	int		nb_q;
	int		nb_q2;
	char	q;

	if (check_temp(temp, data))
		return (-1);
	q = line[*i];
	start = *i;
	count_q(line, i, &nb_q, q);
	nb_q2 = *i;
	while (line[*i] && line[*i] != q)
		*i = *i + 1;
	if (*i == nb_q2 && nb_q % 2 == 0)
		return (get_lexed(copy_quote(temp, line, *i, start), data, QUOTE));
	count_q2(line, i, &nb_q2, nb_q);
	*i = *i - 1;
	if (nb_q == nb_q2)
	{
		if (get_lexed(copy_quote(temp, line, *i, start), data, QUOTE))
			return (-1);
		return (0);
	}
	nb_q = nb_q - nb_q2;
	if (nb_q % 2 == 0)
	{
		while (nb_q)
		{
			if (get_lexed(copy_quote(temp, "\"\"", 2, 0), data, QUOTE))
				return (-1);
			nb_q = nb_q - 2;
			start = start + 2;
		}
		if (get_lexed(copy_quote(temp, line, *i, start), data, QUOTE))
			return (-1);
		return (0);
	}
	return (-2);
}
