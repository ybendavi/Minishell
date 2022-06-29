/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:02:08 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/29 16:44:57 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_path(char **env)
{
	char	*str;

	str = ft_calloc(100);
	if (!str)
		return (NULL);
	str = getenv(PATH);
	if (str)
	{
		free(str);
		return (0);
	}
	else
	{
		free(str);
		return (127);
	}
}

char	**set_env(char **env)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	paths = NULL;
	if (env == NULL)
		return (NULL);
	while (env[i] && ft_strnstr(env[i], "PATH=", 6) == NULL)
		i++;
	if (env[i])
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

int	child_process(t_cmds *cmd, char **env, t_env *envs)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
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
	{
		dup2(cmd->in, 0);
	}
	if (cmd->out != 1 && cmd->out != cmd->pfd_out[1])
	{
		dup2(cmd->out, 1);
	}
	if (is_builtin(cmd) == 0)
		exit(builtins(cmd, envs->env, envs));
	else
	{
		close_fds(cmd);
		if (cmd->cmd && is_builtin(cmd) == 0)
			exit(builtins(cmd, envs->env, envs));
		else if (cmd->cmd && is_builtin(cmd))
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
	}
//	close(0);
//	close(1);
	//dup2(in, 0);
	//dup2(out, 1);
	exit(exec_errors(0, cmd->cmd, envs));
}

int	launcher(t_cmds *cmds, t_env *envs)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmds->cmd, "cd") == 0 || ft_strcmp(cmds->cmd, "exit") == 0)
	{
		if (cmds->next)
			launcher(cmds->next, envs);
		return (0);
	}
	cmds->fork = fork();
	if (cmds->fork < 0)
		perror(NULL);
	if (cmds->fork == 0)
	{
		ret = child_process(cmds, envs->env, envs);
		return (ret);
	}
	else if (cmds->fork > 0)
	{
		if (cmds->in != 0 && cmds->in != -1)
		{
			close(cmds->in);
		}
		if (cmds->prev && cmds->prev->out != 1 && cmds->prev->out != -1)
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
		if (str)
		{
			write(2, str, ft_strlen(str));
			write(2, "\n", 1);
		}
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
		if (ft_strcmp(cmds->cmd, "cd") && ft_strcmp(cmds->cmd, "exit"))
		{
			if (cmds->fork > 0)
			{
				waitpid(cmds->fork, &status, 0);
				if (WIFEXITED(status) != 0)
					status_code = WEXITSTATUS(status);
				else
					status_code = check_sig(status);
				cmds = cmds->next;
			}
		}
		else
		{
			status_code = builtins(cmds, envs->env, envs);
			cmds = cmds->next;
		}
	}
	return (status_code);
}
