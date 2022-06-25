#include "minishell.h"

void	free_pfds(t_cmds *cmds)
{
	while (cmds)
	{
		free(cmds->pfd_in);
		free(cmds->pfd_out);
		cmds = cmds->next;
	}
}

void	free_cmds_table(t_cmds *tbls)
{
	int		i;
	t_cmds	*tmp;

	i = 0;
	if (!tbls)
		return ;
	if (tbls->cmds)
	{
		while (tbls->cmds[i])
		{
			free(tbls->cmds[i]);
			i++;
		}
		free(tbls->cmds);
	}
	if (tbls->cmd)
		free(tbls->cmd);
	if (tbls->path)
		free(tbls->path);
	tmp = tbls->next;
	if (tmp)
		free_cmds_table(tmp);
	free(tbls);
}

void	freeer(t_env *envs)
{
	free_pfds(envs->c_tbls);
	free_cmds_table(envs->c_tbls);
}
