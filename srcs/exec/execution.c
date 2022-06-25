/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:02:08 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/25 18:36:20 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_env(char **env)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 6) == NULL)
		i++;
	paths = ft_split(ft_strchr(env[i], '=') + 1, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!paths[i])
		{
			paths_free(paths);
			return (NULL);
		}
		i++;
	}
	return (paths);
}

int	set_forks(t_env	*envs)
{
	t_cmds	*tmp;

	tmp = envs->c_tbls;
	while (tmp)
	{
		if (tmp->cmds)
			tmp->fork = fork();
		tmp = tmp->next;
	}
	return (0);
}

int	close_fds(t_cmds *cmd)
{	
	t_cmds	*tmp;

	tmp = cmd;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->in != 0 && tmp != cmd)
			close(tmp->in);
		if (tmp->out != 1 && tmp != cmd && tmp != cmd->prev)
			close(tmp->out);
		tmp = tmp->next;
	}
	return (0);
}

int	child_process(t_cmds *cmd, char **env)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
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
	{
		dup2(cmd->in, 0);
	}
	if (cmd->out != 1 && cmd->out != cmd->pfd_out[1])
	{
		dup2(cmd->out, 1);
	}
	close_fds(cmd);
	execve(cmd->cmds[0], cmd->cmds, env);
//	close(0);
//	close(1);
	dup2(in, 0);
	dup2(out, 1);
	if (errno == 2)
		exit(127);
	else if (errno == 8)
		exit(126);
	else
		exit(EXIT_FAILURE);
}

int	launcher(t_cmds *cmds, t_env *envs)
{
	int	ret;

	ret = 0;
	cmds->fork = fork();
	if (cmds->fork < 0)
		perror(NULL);
	if (cmds->fork == 0)
	{
		printf("slt\n");
		ret = child_process(cmds, envs->env);
		return (ret);
	}
	else if (cmds->fork > 0)
	{
		if (cmds->in != 0)
		{
			close(cmds->in);
		}
		if (cmds->prev && cmds->prev->out != 1)
		{
			close(cmds->prev->out);
		}
		if (cmds->next)
			launcher(cmds->next, envs);
	}
	return (ret);
}

int	check_sig(int status)
{
	char	*str;
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		str = sig_error(sig);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		return (128 + sig);
	}
	return (0);
}

int	execution(t_env *envs)
{
	t_cmds	*cmds;
	int		status;
	int		status_code;
	
	if (set_paths(envs) == -1)
	{
		perror(NULL);
		return (-1);
	}
	cmds = envs->c_tbls;
	status = 0;
	status_code = launcher(cmds, envs);
	while (cmds)
	{
		if (cmds->fork > 0)
		{
			waitpid(cmds->fork, &status, 0);
			if (WIFEXITED(status) != 0)
				status_code = WEXITSTATUS(status);
			else
				status_code = check_sig(status);
			printf("status code:%d\n", status_code);
			cmds = cmds->next;
		}
	}
	return (status_code);
}
