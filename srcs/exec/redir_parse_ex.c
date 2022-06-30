/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:31:39 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/01 00:27:17 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_non_buff(t_env *envs, int *fds)
{
	close(fds[1]);
	write(1, "warning: here-document delimited by ", 36);
	write(1, "end-of-file (wanted `file')\n", 29);
	free_all_env(envs);
	exit (0);
}
