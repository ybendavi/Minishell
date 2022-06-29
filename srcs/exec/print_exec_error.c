/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:52:15 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/29 16:52:19 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_error(const char *cmd, t_env *envs, int fd)
{
	if (errno == 2 && ft_strchr(cmd, '/') != NULL)
	{
		perror(cmd);
		free_all_env(envs);
		return (127);
	}
	if (access(cmd, X_OK) == -1)
	{
		perror(cmd);
		free_all_env(envs);
		return (126);
	}
	fd = open(cmd, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		write(2, "Is a directory\n", ft_strlen("Is a directory\n"));
		free_all_env(envs);
		return (126);
	}
	return (0);
}

int	errno_two(const char *cmd, t_env *envs)
{	
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, "command not found\n", ft_strlen("command not found\n"));
	free_all_env(envs);
	return (127);
}

int	exec_errors(int status_code, const char *cmd, t_env *envs)
{
	int	fd;
	int	ret;

	(void)status_code;
	fd = 0;
	write(2, "bash: ", 6);
	ret = 0;
	if (ft_strchr(cmd, '/') != NULL)
	{
		ret = path_error(cmd, envs, fd);
		if (ret != 0)
			return (ret);
	}
	if (errno == 2)
		return (errno_two(cmd, envs));
	if (errno == 13)
	{
		perror(cmd);
		write(2, "Permission denied\n", 18);
		free_all_env(envs);
		return (126);
	}
	free_all_env(envs);
	return (EXIT_FAILURE);
}
