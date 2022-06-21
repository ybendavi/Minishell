/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:02:18 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/20 19:02:34 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	test_path(char *tmp, t_cmds *cmd)
{
	char	*tmp2;

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

char	*test_paths(char *tmp, int i, char **paths, t_cmds *cmd)
{
	while (paths[i] && access(tmp, X_OK) == -1)
	{
		free(tmp);
		tmp = ft_strjoin(paths[i], cmd->cmd);
		if (!tmp)
		{
			paths_free(paths);
			return (NULL);
		}
		i++;
	}
	return (tmp);
}

int	set_path(t_cmds	*cmd, char **paths)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	if (access(cmd->cmds[0], X_OK) != -1)
		return (0);
	tmp = ft_strjoin(paths[i], cmd->cmd);
	if (!tmp)
	{
		paths_free(paths);
		return (-1);
	}
	i++;
	tmp = test_paths(tmp, i, paths, cmd);
	if (!tmp)
		return (-1);
	test_path(tmp, cmd);
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
