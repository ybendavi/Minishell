#include "minishell.h"

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
	tmp = tbls->next;
	if (tmp)
		free_cmds_table(tmp);
	free(tbls);
}
//Trouver une solution pour free les pfd.
