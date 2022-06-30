/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:31:39 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/30 23:15:19 by ccottin          ###   ########.fr       */
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

void	exec_redir(char **buff, t_env *envs, t_cmds *cmd)
{
	write(1, *buff, ft_strlen(*buff));
	write(1, "\n", 1);
	if (*buff)
		free(*buff);
	*buff = NULL;
	*buff = readline(">");
	if (!*buff)
		exit_non_buff(envs, cmd->pfd_in);
}
