/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:51:41 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/09 20:53:02 by ybendavi         ###   ########.fr       */
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
	if (cmd->in != 0 && cmd->in != -3 && cmd->in != -1)
	{
		dup2(cmd->in, 0);
	}
	if (cmd->out != 1 && cmd->out != -3 && cmd->out != -1)
	{
		dup2(cmd->out, 1);
	}
}

int	exec_no_pipe(t_cmds *cmd, t_env *envs)
{
	int	status_code;

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
	close(0);
	close(1);
	close(2);
	return (status_code);
}
