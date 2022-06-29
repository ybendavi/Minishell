/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:38:51 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/29 21:16:16 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_fds(t_cmds *cmd)
{
	t_cmds	*tmp;

	tmp = cmd;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->in != 0 && tmp != cmd && tmp->in != -1)
			close(tmp->in);
		if (tmp->out != 1 && tmp != cmd && tmp != cmd->prev && tmp->out != -1)
			close(tmp->out);
		tmp = tmp->next;
	}
	return (0);
}

void	quit_proc(t_cmds *tmp, t_env *envs)
{
	close_fds(tmp);
	if (tmp->in != 0 && tmp->in != -1)
	{
		close(tmp->in);
	}
	if (tmp->out != 1 && tmp->out != -1)
		close(tmp->out);
	freeer(envs);
	free_lexed(envs);
	free_parsed(envs);
	free_all(envs);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

int	no_builtin(t_cmds *cmd, char **env, t_env *envs, int ret)
{
	close_fds(cmd);
	if (ret == 127)
	{
		errno = 2;
		exec_errors(127, cmd->cmd, envs);
		exit(127);
	}
	if (cmd->cmd && is_builtin(cmd) == 0)
		exit(builtins(cmd, envs->env, envs));
	else if (cmd && cmd->cmd && is_builtin(cmd))
	{
		execve(cmd->path, cmd->cmds, env);
	}
	else
	{
		freeer(envs);
		free_lexed(envs);
		free_parsed(envs);
		free_all(envs);
		rl_clear_history();
		exit(0);
	}
	return (0);
}

int	child_process(t_cmds *cmd, char **env, t_env *envs, int ret)
{
	if (cmd->in == -1 || cmd->out == -1)
		quit_proc(cmd, envs);
	if (cmd->pfd_in[0] != -1)
	{
		close(cmd->pfd_in[1]);
		dup2(cmd->pfd_in[0], 0);
		close(cmd->pfd_in[0]);
	}
	if (cmd->pfd_out[0] != -1)
	{
		close(cmd->pfd_out[0]);
		dup2(cmd->pfd_out[1], 1);
		close(cmd->pfd_out[1]);
	}
	if (cmd->in != 0 && cmd->in != cmd->pfd_in[0])
		dup2(cmd->in, 0);
	if (cmd->out != 1 && cmd->out != cmd->pfd_out[1])
		dup2(cmd->out, 1);
	if (is_builtin(cmd) == 0)
		exit(builtins(cmd, envs->env, envs));
	else
		no_builtin(cmd, env, envs, ret);
	exit(exec_errors(0, cmd->cmd, envs));
}
