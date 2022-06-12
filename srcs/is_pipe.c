#include "minishell.h"

int	is_pipe(unsigned int i, t_env *data)
{
	if (i == 0)
		return (-3);
	if (data->parsed[data->nb_parsed - 1].type == PIPE
		|| data->parsed[data->nb_parsed - 1].type == ENV)
		return (-3);
	else
	{
		if (get_parsed(data, data->lexed[i]))
			return (-1);
	}
	return (0);
}
