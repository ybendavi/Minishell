/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:02:08 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/07 18:44:11 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

int	launcher(t_cmds *cmds, t_env *envs, int retu)
{
	int	ret;

	ret = 0;
	status = 0;
	if (is_builtin(cmds) == 0 && cmds->pfd_in[0] == -1
		&& cmds->pfd_out[0] == -1)
	{
		if (cmds->next)
			launcher(cmds->next, envs, retu);
		return (0);
	}
	cmds->fork = fork();
	if (cmds->fork < 0)
		perror(NULL);
	if (cmds->fork == 0)
	{
		ret = child_process(cmds, envs->env, envs, retu);
		return (ret);
	}
	else if (cmds->fork > 0)
	{
		parent_process(cmds, status);
		if (cmds->next)
			launcher(cmds->next, envs, retu);
	}
	return (ret);
}

int	check_sig(int status, t_env *envs)
{
	char	*str;
	int		sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (envs->nb_sig != sig)
		{
			envs->nb_sig = sig;
			str = sig_error(sig);
			if (str)
			{
				write(2, str, ft_strlen(str));
				write(2, "\n", 1);
			}
		}
		return (128 + sig);
	}
	return (0);
}

int	child_waiter(t_cmds *cmds, t_env *envs, int status, int status_code)
{
	waitpid(cmds->fork, &status, 0);
	if (WIFEXITED(status) != 0)
		status_code = WEXITSTATUS(status);
	else
		status_code = check_sig(status, envs);
	return (status_code);
}

int	exec_loop(t_cmds *cmds, int status, int status_code, t_env *envs)
{
	while (cmds)
	{
		if (is_builtin(cmds) || (is_builtin(cmds) == 0
				&& (cmds->pfd_in[0] != -1 || cmds->pfd_out[0] != -1)))
		{
			if (cmds->fork > 0)
			{
				if (!cmds->delim)
					status_code = child_waiter(cmds, envs, status, status_code);
				cmds = cmds->next;
			}
		}
		else
		{
			status_code = exec_no_pipe(cmds, envs);
			cmds = cmds->next;
		}
	}
	return (status_code);
}

int	execution(t_env *envs)
{
	t_cmds	*cmds;
	int		status;
	int		status_code;
	int		ret;

	g_sig = 2;
	ret = set_paths(envs);
	if (ret == -1)
		return (-1);
	cmds = envs->c_tbls;
	status = 0;
	status_code = launcher(cmds, envs, ret);
	status_code = exec_loop(cmds, status, status_code, envs);
	return (status_code);
}
