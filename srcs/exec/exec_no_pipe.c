/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:51:41 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/08 22:56:23 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_env *envs)
{
	close_fds(envs->c_tbls);
	close(0);
	close(1);
	close(2);
	free_all_env(envs);
}

void	redir_handler(t_cmds *cmd)
{
	if (cmd->in != 0 && cmd->in != cmd->pfd_in[0] && cmd->in != -3)
	{
		dup2(cmd->in, 0);
		close(cmd->in);
		cmd->in = -3;
	}
	if (cmd->out != 1 && cmd->out != cmd->pfd_out[1] && cmd->out != -3)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
		cmd->out = -3;
	}
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
	if (cmd->out != 1 && cmd->out != -3)
	{
		close(cmd->out);
		cmd->out = -3;
	}
	if (cmd->in != 0 && cmd->in != -3)
	{
		close(cmd->in);
		cmd->out = -3;
	}
	dup2(in, 0);
	close(in);
	dup2(out, 1);
	close(out);
	return (status_code);
}
