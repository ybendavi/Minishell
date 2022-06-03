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
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (paths);
}

int	set_path(t_cmds	*cmd, char **paths)
{
	char	*tmp;
	char	*tmp2;
	int	i;

	tmp = NULL;
	i  = 0;
	if (access(cmd->cmds[0], X_OK) != -1)
		return (0);
	tmp = ft_strjoin(paths[i], cmd->cmd);
	i++;
	while (paths[i] && access(tmp, X_OK) == -1)
	{
		free(tmp);
		tmp = ft_strjoin(paths[i], cmd->cmd);
		i++;
	}
	if (access(tmp, X_OK) != -1)
	{
		tmp2 = cmd->cmds[0];
		cmd->cmds[0] = tmp;
		free(tmp2);
	}
	else
	{
		perror(cmd->cmds[0]);
		free(tmp);
	}
	return (0);
}

int	set_paths(t_env *envs)
{
	char	**paths;
	t_cmds	*tmp;

	paths = set_env(envs->env);
	tmp = envs->c_tbls;
	while (tmp)
	{
		set_path(tmp, paths);
		tmp = tmp->next;
	}
	return (0);
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

int	child_process(t_cmds *cmd, char **env)
{
	if (cmd->pfd_in[0] != -1 || cmd->pfd_out[0] != -1)
	{
		if (cmd->in == cmd->pfd_in[0])
			close(cmd->pfd_in[1]);
		if (cmd->out == cmd->pfd_out[1])
			close(cmd->pfd_out[0]);
	}
	if (cmd->in != 0)
	{
		if (dup2(cmd->in, 0) == -1)
			return (-1);
		if (cmd->pfd_out[0] != -1 && cmd->pfd_out[1])
		{
			if (cmd->out == cmd->pfd_out[1])
			{
				dup2(cmd->pfd_out[1], 1);
				close(cmd->pfd_out[1]);
			}
		}
	}
	if (cmd->out != 1)
	{
		if (dup2(cmd->out, 1) == -1)
			return (-1);
		if (cmd->pfd_in[0] != -1 && cmd->pfd_in[0])
		{
			if (cmd->in == cmd->pfd_in[0])
			{
				dup2(cmd->pfd_in[0], 0);
				close(cmd->pfd_in[0]);
			}
		}
	}
	execve(cmd->cmds[0], cmd->cmds, env);
	perror(NULL);
	return (-1);
}

int	parent_process(int status, t_cmds *cmds)
{

	while (cmds)
	{
		if (cmds->pfd_out[0] != -1 && cmds->out == cmds->pfd_out[1])
			close(cmds->pfd_out[1]);
		if (cmds->pfd_in[0] != -1 && cmds->in == cmds->pfd_in[0])
			close(cmds->pfd_in[0]);
		waitpid(cmds->fork, &status, 0);
		cmds = cmds->next;
	}
	return (0);
}


int	execution(t_env *envs)
{
	t_cmds	*cmds;
	int	status;

	status = 0;
	set_paths(envs);
	set_forks(envs);
	cmds = envs->c_tbls;
	while (cmds)
	{
		if (cmds->fork < 0)
			perror(NULL);
		if (cmds->fork == 0)
			child_process(cmds, envs->env);
		if (cmds->next == NULL && cmds->fork != 0)
			parent_process(status, envs->c_tbls);
		cmds = cmds->next;
	}
	return (0);
}
