/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:17:59 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/05 17:41:28 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_parsing_errors(t_env *env)
{
	if (env->nb_parsed == 0)
		write(1, "\n", 1);
	else if (env->nb_parsed == 1)
		{
			if (ft_cmp(env->parsed[0].token, "!")
			|| ft_cmp(env->parsed[0].token, ":")
			|| ft_cmp(env->parsed[0].token, "#"))
			{
				write(1, "\n", 1);
				return (-4);
			}
		}
	if (env->parsed[env->nb_parsed - 1].type != STR
		env->parsed[env->nb_parsed - 1].type != QUOTE)
		return (-5);
	if (env->parsed[0].type == STR || env->parsed[0].type == QUOTE)
		concat_quote(env); //faire ca dans le parsing
	return (0);
}


