/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:51:41 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/10 22:44:29 by ybendavi         ###   ########.fr       */
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

int	delim_no_pipe(t_env *envs, t_cmds *cmd)
{
	int		status;
	pid_t	child;

	status = 0;
	child = fork();
	if (child < 0)
		return (-2);
	if (child == 0)
	{
		lim_handler(cmd, envs);
		free_exec(envs);
		exit(0);
	}
	else
	{
		waitpid(child, &status, 0);
		if (WIFEXITED(status) != 0)
		{
			if (WEXITSTATUS(status) != 0)
				return (130);
		}
		return (0);
	}
	return (0);
}

void	in_out_handler(t_cmds *cmd, int in, int out)
{	
	if (cmd->out != 1 && cmd->out != -3)
	{
		close(cmd->out);
		cmd->out = -3;
		close(0);
	}
	if (cmd->in != 0 && cmd->in != -3)
	{
		close(cmd->in);
		cmd->out = -3;
		close(1);
	}
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

int	exec_no_pipe(t_cmds *cmd, t_env *envs)
{
	int	status_code;
	int	in;
	int	out;

	status_code = 0;
	if (cmd->delim)
		status_code = delim_no_pipe(envs, cmd);
	in = dup(0);
	out = dup(1);
	redir_handler(cmd);
	if (is_builtin(cmd) == 0 && status_code == 0)
		status_code = builtins(cmd, in, out, envs);
	in_out_handler(cmd, in, out);
	return (status_code);
}
