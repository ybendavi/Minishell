/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:51:41 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/30 01:52:23 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_handler(t_cmds *cmd)
{
	if (cmd->in != 0 && cmd->in != cmd->pfd_in[0])
		dup2(cmd->in, 0);
	if (cmd->out != 1 && cmd->out != cmd->pfd_out[1])
		dup2(cmd->out, 1);
}

int	exec_no_pipe(t_cmds *cmd, t_env *envs)
{
	int	in;
	int	out;
	int	status_code;

	in = dup(0);
	out = dup(1);
	status_code = 0;
	redir_handler(cmd);
	if (is_builtin(cmd) == 0)
		status_code = builtins(cmd, envs->env, envs);
	if (cmd->out != 1)
		close(cmd->out);
	if (cmd->in != 0)
		close(cmd->in);
	dup2(in, 0);
	dup2(out, 1);
	return (status_code);
}
