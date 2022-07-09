/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:38:51 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/09 14:26:04 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

void	close_fds_two(t_cmds *tmp)
{
	if (tmp->lim[0] != -1 && tmp->lim[0] != -3)
	{
		close(tmp->lim[0]);
		tmp->lim[0] = -3;
	}
	if (tmp->lim[1] != -1 && tmp->lim[1] != -3)
	{
		close(tmp->lim[1]);
		tmp->lim[1] = -3;
	}
}

int	close_fds(t_cmds *cmd)
{
	t_cmds	*tmp;

	tmp = cmd;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
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
		close_fds_two(tmp);
		tmp = tmp->next;
	}
	return (0);
}

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

void	exit_non_buff(t_env *envs, int *fds)
{
	if (fds[1] != -1 && fds[1] != -3)
	{
		close(fds[1]);
		fds[1] = -3;
	}
	write(2, "warning: here-document delimited by ", 36);
	write(2, "end-of-file (wanted `file')\n", 29);
	free_exec(envs);
	exit (0);
}

void	handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 42;
		close(0);
	}
}

void	exit_int(t_env *envs, char **buff)
{
	if (g_sig == 42)
	{
		if (buff)
		{
			if (*buff)
				free(*buff);
		}
		free_exec(envs);
		exit(1);
	}
}

void	exec_redir(char **buff, t_env *envs, t_cmds *cmd)
{
	exit_int(envs, buff);
	write(cmd->lim[1], *buff, ft_strlen(*buff));
	write(cmd->lim[1], "\n", 1);
	if (*buff)
		free(*buff);
	*buff = NULL;
	*buff = readline(">");
	exit_int(envs, buff);
	if (!*buff)
		exit_non_buff(envs, cmd->lim);
}

void	set_sig_child(t_env *envs)
{
	sigemptyset(&(envs->sig_q.sa_mask));
	sigaddset(&(envs->sig_q.sa_mask), SIGQUIT);
	envs->sig_q.sa_handler = SIG_IGN;
	envs->sig_q.sa_flags = 0;
	sigaction(SIGQUIT, &(envs->sig_q), NULL);
	sigemptyset(&(envs->sig_i.sa_mask));
	sigaddset(&(envs->sig_i.sa_mask), SIGINT);
	envs->sig_i.sa_handler = &handler_child;
	envs->sig_i.sa_flags = 0;
	sigaction(SIGINT, &(envs->sig_i), NULL);
}

int	lim_handler(t_cmds *cmd, t_env *envs)
{
	char	*buff;
	int	i;

	i = 0;
	if (!cmd->delim)
		return (0);
	set_sig_child(envs);
	exit_int(envs, &buff);
	while (cmd->delim[i + 1] != NULL)
	{
		buff = readline(">");
		exit_int(envs, &buff);
		i++;
		if (!buff)
			exit_non_buff(envs, cmd->lim);
		else
			free(buff);
	}
	buff = readline(">");
	if (!buff)
		exit_non_buff(envs, cmd->lim);
	while (ft_strncmp(buff, cmd->delim[i], ft_strlen(buff)) != 0
		|| ft_strncmp(buff, cmd->delim[i], ft_strlen(cmd->delim[i])) != 0)
		exec_redir(&buff, envs, cmd);
	if (buff)
		free(buff);
	close(cmd->pfd_in[1]);
	dup2(cmd->lim[0], 0);
	close(cmd->lim[0]);
	return (0);
}

int	child_process(t_cmds *cmd, char **env, t_env *envs, int ret)
{
	exit_int(envs, NULL);
	if (cmd->delim)
		lim_handler(cmd, envs);
	envs->sig_i.sa_handler = SIG_DFL;
	sigaction(SIGINT, &(envs->sig_i), NULL);
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
