/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:34:10 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/06 17:26:13 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_tok(char *str, int size, t_token_type type, t_token *var)
{
	int	i;

	var->token = ft_calloc(size + 1);
	if (!var)
		return (-1);
	i = 0;
	while (i < size)
	{
		var->token[i] = str[i];
		i++;
	}
	var->size = size;
	var->type = type;
	return (0);
}

int	set_token_list(int i, t_token *var)
{
	if (i == 0)
		return (set_tok(">>", 2, 0, var));
	if (i == 1)
		return (set_tok("<<", 2, 1, var));
	if (i == 2)
		return (set_tok(">", 1, 2, var));
	if (i == 3)
		return (set_tok("<", 1, 3, var));
	if (i == 4)
		return (set_tok("|", 1, 4, var));
	if (i == 5)
		return (set_tok(" ", 1, 5, var));
	if (i == 6)
		return (set_tok("\t", 1, 5, var));
	if (i == 7)
		return (set_tok("\n", 1, 5, var));
	if (i == 8)
		return (set_tok("\v", 1, 5, var));
	if (i == 9)
		return (set_tok("\f", 1, 5, var));
	if (i == 10)
		return (set_tok("\r", 1, 5, var));
	if (i == 11)
		return (set_tok("$", 1, 6, var));
	return (0);
}

int	token_init(t_env *data)
{
	int	i;

	data->tab = ft_calloc(sizeof(t_token) * 12 + 1);
	if (!data->tab)
		return (-1);
	i = 0;
	while (i < 12)
	{
		if (set_token_list(i, &(data->tab[i])) == -1)
			return (-1);
		i++;
	}
	return (0);
}
