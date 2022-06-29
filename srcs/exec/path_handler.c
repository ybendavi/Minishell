/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:02:18 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/29 21:10:33 by ybendavi         ###   ########.fr       */
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

	tmp2 = cmd->path;
	cmd->path = tmp;
	free(tmp2);
	if (access(tmp, X_OK) == -1)
	{
		return (0);
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
	if (ft_strchr(cmd->cmd, '/') != NULL)
	{
		return (0);
	}
	tmp = ft_strjoin(paths[i], cmd->cmd);
	if (!tmp)
	{
		paths_free(paths);
		return (-1);
	}
	i++;
	tmp = test_paths(tmp, i, paths, cmd);
	if (!tmp)
	{
		return (-1);
	}
	return (test_path(tmp, cmd));
}

int	set_paths(t_env *envs)
{
	char	**paths;
	t_cmds	*tmp;
	int		ret;

	paths = set_env(envs->env);
	ret = set_path_error(paths);
	if (ret)
		return (ret);
	tmp = envs->c_tbls;
	while (tmp)
	{
		if (tmp->cmd)
		{
			tmp->path = ft_strdup(tmp->cmd);
			ret = set_path(tmp, paths);
			if (ret == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	paths_free(paths);
	return (ret);
}
