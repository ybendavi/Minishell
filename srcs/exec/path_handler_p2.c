/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:08:49 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/29 21:08:51 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_path_error(char **paths)
{
	if (!paths)
		return (-1);
	if (strcmp(*paths, "command not found") == 0)
	{
		paths_free(paths);
		return (127);
	}
	return (0);
}
