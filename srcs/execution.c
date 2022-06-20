#include "minishell.h"

void	paths_free(char **paths)
{
	int	i;

	i = 0;
	if (paths)
	{
		while (paths[i])
		{
			free(paths[i]);
			i++;
		}
		free(paths);
	}
}

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
	if (!tmp)
	{
		paths_free(paths);
		return (-1);
	}
	i++;
	while (paths[i] && access(tmp, X_OK) == -1)
	{
		free(tmp);
		tmp = ft_strjoin(paths[i], cmd->cmd);
		if (!tmp)
		{
			paths_free(paths);
			return (-1);
		}
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
	if (!paths)
		return (-1);
	tmp = envs->c_tbls;
	while (tmp)
	{
		if (set_path(tmp, paths) == -1)
			return (-1);
		tmp = tmp->next;
	}
	paths_free(paths);
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
	t_cmds *tmp;

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
	execve(cmd->cmds[0], cmd->cmds, env);
	return (0);
}

int	launcher(t_cmds *cmds, t_env *envs)
{
	int	status;

	cmds->fork = fork();
	if (cmds->fork < 0)
		perror(NULL);
	if (cmds->fork == 0)
	{
		child_process(cmds, envs->env);
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
		waitpid(cmds->fork, &status, 0);
	}
	return (0);
}


void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;

	if (sig == SIGPIPE)
	{
		write(1, "hello\n", 6);
		kill(info->si_pid, SIGINT);
	}
}

void	init(struct sigaction *sig)
{
	sig->sa_sigaction = &handler;
	if (sigemptyset(&(sig)->sa_mask) == -1)
		return ;
	sigaddset(&(sig)->sa_mask, SIGPIPE);
	sig->sa_flags = SA_SIGINFO;
}

int	execution(t_env *envs)
{
	t_cmds	*cmds;
//	struct sigaction	sig;
	int	status;

//	init(&sig);
	if (set_paths(envs) == -1)
		return (-1);
	//set_forks(envs);
	cmds = envs->c_tbls;
	status = 0;
	launcher(cmds, envs);
	return (0);
}
