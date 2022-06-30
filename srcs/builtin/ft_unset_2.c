/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:12:49 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/30 23:15:40 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_error(char **neww)
{
	int	y;

	y = 0;
	while (neww[y])
		free(neww[y++]);
	free(neww);
	return (-1);
}
