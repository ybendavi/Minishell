/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:42:15 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/29 18:50:41 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**set_env(char **env)
{
	char	**paths;
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

void	parent_process(t_cmds *cmds)
{	
	if (cmds->in != 0 && cmds->in != -1)
		close(cmds->in);
	if (cmds->prev && cmds->prev->out != 1 && cmds->prev->out != -1)
		close(cmds->prev->out);
}
