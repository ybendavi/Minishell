/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:03:51 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/06 15:59:17 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **argv, char **env)
{
	t_env	envs;
	//t_cmds	*tmp;
	//int	i;
	//(void)argv;
	//if (ac > 1)
	//	printf("This program doesn't take arguments.\n");
	(void)ac;
	envs.env = env;
	parsing(&envs, argv[1]);
	execution(&envs);
	//i = 0;
	//tmp = envs.c_tbls;
	/*if (tmp)
	{
		while (tmp)
		{
			i = 0;
			if (tmp->cmds)
			{
				while (tmp->cmds[i])
				{
					printf("cmds:%s\n", tmp->cmds[i]);
					i++;
				}
			}
			if (tmp->cmd)
				printf("cmd:%s\n", tmp->cmd);
			printf("in:%d\nout:%d\n", tmp->in, tmp->out);
			if (tmp->in)
				close(tmp->in);
			if (tmp->out)
				close(tmp->out);

			tmp = tmp->next;
		}
	}*/
	freeer(&envs);
	return (0);
}
