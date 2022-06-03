/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:03:51 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/03 14:05:58 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **argv, char **env)
{
	t_env	envs;
	t_cmds	*tmp;
	//int	i;
	//(void)argv;
	//if (ac > 1)
	//	printf("This program doesn't take arguments.\n");
	(void)ac;
	envs.env = env;
	parsing(&envs, argv[1]);
	execution(&envs);
	//i = 0;
	tmp = envs.c_tbls;
	/*if (envs.c_tbls)
	{
		while (envs.c_tbls)
		{
			i = 0;
			if (envs.c_tbls->cmds)
			{
				while (envs.c_tbls->cmds[i])
				{
					printf("cmds:%s\n", envs.c_tbls->cmds[i]);
					i++;
				}
			}
			if (envs.c_tbls->cmd)
				printf("cmd:%s\n", envs.c_tbls->cmd);
			printf("in:%d\nout:%d\n", envs.c_tbls->in, envs.c_tbls->out);
			if (envs.c_tbls->in)
				close(envs.c_tbls->in);
			if (envs.c_tbls->out)
				close(envs.c_tbls->out);

			envs.c_tbls = envs.c_tbls->next;
		}
	}*/
	free_cmds_table(tmp);
	return (0);
}
