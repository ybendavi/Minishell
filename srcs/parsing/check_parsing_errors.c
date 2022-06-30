/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:17:59 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/30 16:15:43 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parsing_errors(t_env *data)
{
	if (data->nb_parsed == 1)
		return (2);
	if (data->parsed[data->nb_parsed - 2].type != STR)
		return (-5);
	return (0);
}
