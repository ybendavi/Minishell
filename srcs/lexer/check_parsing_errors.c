/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:17:59 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/06 20:58:11 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_parsing_errors(t_env *data)
{
	if (data->nb_parsed == 0)
		return (0);//on scomprend en gros c la fin
	else if (data->nb_parsed == 1)
		{
			if (ft_cmp(data->parsed[0].token, "!")
			|| ft_cmp(data->parsed[0].token, ":")
			|| ft_cmp(data->parsed[0].token, "#"))
			{
				write(1, "\n", 1);
		//		return (-4);
			}
		}
	if (data->parsed[data->nb_parsed - 1].type != STR
		&& data->parsed[data->nb_parsed - 1].type != PIPE)
		return (-5);
	return (0);
}


