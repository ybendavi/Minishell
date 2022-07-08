/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:38:51 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/08 14:24:59 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_proc(t_cmds *tmp, t_env *envs)
{
	close_fds(tmp);
	if (tmp->in != 0 && tmp->in != -1 && tmp->in != -3)
	{
		close(tmp->in);
		tmp->in = -3;
	}
	if (tmp->out != 1 && tmp->out != -1 && tmp->out != -3)
	{
		close(tmp->out);
		tmp->out = -3;
	}
	free_exec(envs);
	exit(EXIT_FAILURE);
}

int	no_builtin(t_cmds *cmd, char **env, t_env *envs, int ret)
{
	close_fds(cmd);
	if (ret == 127)
	{
		errno = 2;
		write(2, "bash: ", ft_strlen("bash: "));
		exit(errno_two(cmd->cmd, envs));
	}
	if (cmd->cmd && is_builtin(cmd) == 0)
		exit(builtins(cmd, envs->env, envs));
	else if (cmd && cmd->path && cmd->cmd && is_builtin(cmd))
	{
		execve(cmd->path, cmd->cmds, env);
	}
	else
	{
		free_exec(envs);
		exit(0);
	}
	return (0);
}

void	fork_handler(t_cmds *cmd)
{	
	if (cmd->pfd_in[0] != -1 && cmd->pfd_in[0] != -3)
	{
		close(cmd->pfd_in[1]);
		cmd->pfd_in[1] = -3;
		dup2(cmd->pfd_in[0], 0);
		close(cmd->pfd_in[0]);
		cmd->pfd_in[0] = -3;
	}
	if (cmd->pfd_out[0] != -1 && cmd->pfd_out[0] != -3)
	{
		close(cmd->pfd_out[0]);
		cmd->pfd_out[0] = -3;
		dup2(cmd->pfd_out[1], 1);
	}
}

int	child_process(t_cmds *cmd, char **env, t_env *envs, int ret)
{
	exit_int(envs, NULL);
	if (cmd->delim)
		lim_handler(cmd, envs);
	envs->sig_q.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &(envs->sig_q), NULL);
	fork_handler(cmd);
	if (cmd->in == -1 || cmd->out == -1)
		quit_proc(cmd, envs);
	redir_handler(cmd);
	if (is_builtin(cmd) == 0)
		exit(builtins(cmd, envs->env, envs));
	else
		no_builtin(cmd, env, envs, ret);
	exit(exec_errors(0, cmd->cmd, envs));
}
