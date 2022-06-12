#include "minishell.h"

void	free_lexed(t_env *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_token)
	{
		if (data->lexed[i].token)
		{
			free(data->lexed[i].token);
			data->lexed[i].token = NULL;
		}
		i++;
	}
	if (data->lexed)
	{
		free(data->lexed);
		data->lexed = NULL;
	}
	data->nb_token = 0;
}

void	free_parsed(t_env *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_parsed)
	{
		if (data->parsed[i].token)
		{
			free(data->parsed[i].token);
			data->parsed[i].token = NULL;
		}
		i++;
	}
	if (data->parsed)
	{	
		free(data->parsed);
		data->parsed = NULL;
	}
	data->nb_parsed = 0;
}

int	ft_return(int ret, t_env *data, char **buff)
{
	unsigned int	i;
	
	if (ret == -1)
		write(2, "Malloc error.\n", 14);
	if (ret == -2)
		write(1, "Lone quote.\n", 12);
	if (ret == -3)
		printf("bash : syntax error near unexpected token `%s'\n", data->error);
	if (ret == -5)
		printf("bash : syntax error near unexpected token `newline'\n");
	if (*buff)
		free(*buff);
	i = 0;
	while (ret == 0 && i < 12)
	{
		if (data->tab[i].token)
			free(data->tab[i].token);
		i++;
	}
	if (data->tab)
		free(data->tab);
	if (ret < -2)
		free_parsed(data);
	if (ret < 0 && ret > -4)
		free_lexed(data);
	if (ret == 0)
		exit(0);
	return (0);
}
