/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:42:15 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/09 13:45:52 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

char	**path_selector(char **paths)
{	
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
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

char	**error_env(void)
{
	char	*tmp;
	char	**paths;

	tmp = ft_strdup("command not found");
	paths = ft_split(tmp, 0);
	free(tmp);
	return (paths);
}

char	**set_env(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	if (env == NULL)
		return (error_env());
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (error_env());
	if (env[i])
		paths = ft_split(ft_strchr(env[i], '=') + 1, ':');
	if (!paths)
		return (NULL);
	return (path_selector(paths));
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

void	parent_process(t_cmds *cmds, int status, t_env *envs)
{	
	(void) envs;
	if (cmds->in != 0 && cmds->in != -1 && cmds->in != -3)
	{
		close(cmds->in);
		cmds->in = -3;
	}
	if (cmds->prev && cmds->prev->out != 1 && cmds->prev->out != -1
		&& cmds->prev->out != -3)
	{
		close(cmds->prev->out);
		cmds->prev->out = -3;
	}
	if (cmds->delim)
	{
		if (cmds->lim[0] != -1 && cmds->lim[0] != -3)
		{
			close(cmds->lim[0]);
			cmds->lim[0] = -3;
		}
		if (cmds->lim[1] != -1 && cmds->lim[1] != -3)
		{
			close(cmds->lim[1]);
			cmds->lim[1] = -3;
		}
	//	envs->sig_i.sa_handler = &kill_int;
	//	sigaction(SIGINT, &(envs->sig_i), NULL);
	//	if (g_sig == 42)
	//		kill(cmds->fork, SIGINT);
		waitpid(cmds->fork, &status, 0);
		if (WIFEXITED(status) != 0)
		{
			printf("status:%d\n", WEXITSTATUS(status));
			//if (WEXITSTATUS(*status) == 130)
			//{
		//		g_sig = 42;
		//		printf("global:%d\n", g_sig);
		//	}
		}
		//if (!WIFSIGNALED(*status))
		//{
			//if (WTERMSIG(*status) == SIGINT)
			//	g_sig = 42;
		//}
	//	envs->sig_i.sa_handler = &handler_sig;
	//	sigaction(SIGINT, &(envs->sig_i), NULL);
	}
}
