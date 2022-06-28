#include "minishell.h"

int	handle_buff(t_env *data, char **buff)
{
	int	ret;

	ret = lexer(*buff, data);
	if (ret)
	{
		free(*buff);
		*buff = NULL;
		return (ft_return(ret, data));
	}
	printf("/°\\_/°\\_/°\\_/°\\ Lexer Output /°\\_/°\\_/°\\_/°\\\n\n");
		unsigned int	i = 0;
		while (i < data->nb_token)
		{
			printf("%d = %d %d %s\n", i, data->lexed[i].type, data->lexed[i].size, data->lexed[i].token);
			i++;
		}

	ret = init_parser(data, data->env);
	if (ret)
		return (ft_return(ret, data));
	add_history(*buff);
	free(*buff);
	*buff = NULL;
	return (0);
}

void	reset(t_env *data)
{
	set_null(data);	
}
	
int	main(int ac, char **av, char **env)
{
	t_env	data;
	char	*buff;
	int		ret;

	(void)ac;
	(void)av;
	if (ft_init(&data, env))
		ft_return(1, &data);
	data.status_code = 0;
	while (7)
	{
		buff = readline("minishell$ ");
		if (!buff)
		{
			data.status_code = ft_return(1, &data);
			write(1, "\n", 1);
		}
		data.status_code = handle_buff(&data, &buff);
		if (!data.status_code)
		{
		//test
			unsigned int i = 0;
			printf("/°\\_/°\\_/°\\_/°\\ Parser Output /°\\_/°\\_/°\\_/°\\\n\n");
			while (i < data.nb_parsed)
			{
				printf("%d = %d %d %s\n", i, data.parsed[i].type, data.parsed[i].size, data.parsed[i].token);
				i++;
			}
			printf("______________________________________________________\n");
		//end-test
			ret = parsing(&data);
		//	if (ret)
		//		return (ret);
		//test	
			t_cmds	*tmp;
			i = 0;
			tmp = data.c_tbls;
			if (tmp)
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
					tmp = tmp->next;
				}
				printf("\n======= OUTPUT =======\n");
			}
		//end-test
			data.status_code = execution(&data);
			freeer(&data);
		}
		else
		{
			freeer(&data);
			free_lexed(&data);
			free_parsed(&data);
		}
		printf("status_code:%d\n", data.status_code);
		
		reset(&data);
	}
	return(0);
}
