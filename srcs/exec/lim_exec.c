/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lim_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:14:33 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/08 14:26:46 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	iter_delim(t_cmds *cmd, t_env *envs, char *buff)
{	
	int	i;

	i = 0;
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
	return (i);
}

int	lim_handler(t_cmds *cmd, t_env *envs)
{
	char	*buff;
	int		i;

	if (!cmd->delim)
		return (0);
	buff = NULL;
	i = iter_delim(cmd, envs, buff);
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
