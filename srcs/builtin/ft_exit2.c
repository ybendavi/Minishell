/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:49:28 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/10 23:26:46 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_write(t_env *data)
{
	t_cmds	*tmp;

	tmp = data->c_tbls;
	while (tmp && tmp->cmd
		&& ft_strncmp(tmp->cmd, "exit", ft_strlen(tmp->cmd)) != 0)
	{
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (tmp->pfd_out[1] != -1)
			write(1, "exit\n", 5);
	}
}

void	exit_fd(int in, int out)
{
	if (in != 0 && out != 1)
	{
		close(in);
		close(out);
	}
	close(0);
	close(1);
	close(2);
}
