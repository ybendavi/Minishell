/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parse_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:31:39 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/06 21:26:21 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void	redir_process(t_token *token, t_cmds *cmd, t_env *envs)
{
	char	*buff;

	close(cmd->pfd_in[0]);
	cmd->pfd_in[0] = -3;
	buff = readline(">");
	if (!buff)
		exit_non_buff(envs, cmd->pfd_in);
	while (ft_strncmp(buff, token[1].token, ft_strlen(buff)) != 0)
		exec_redir(&buff, envs, cmd);
	if (buff)
		free(buff);
	close(cmd->pfd_in[1]);
	free_exec(envs);
	exit(0);
}

