#include "minishell.h"

int	ft_cmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	if (ft_strlen(s1) == i && ft_strlen(s2) == i)
		return (1);
	return (0);
}

int	handle_buff(t_env *data, char **buff, char **env)
{
	int	ret;

	if (ft_cmp(*buff, "exit"))
		return (ft_return(0, data, buff));
	ret = lexer(*buff, data);
	if (ret)
		ft_return(ret, data, buff);
	free(*buff);
	*buff = NULL;
	ret = init_parser(data, env);
	if (ret)
		ft_return(ret, data, buff);
	ret = check_parsing_errors(data);
	if (ret)
		ft_return(ret, data, buff);
	return (0);
}
	
int	main(int ac, char **av, char **env)
{
	t_env	data;
	char	*buff;
	int		ret;

	(void)ac;
	(void)av;
	if (ft_init(&data))
		return (ft_return(-1, &data, NULL)); //NULL creer une faute memoire
	data.env = env;
	while (7)
	{
		buff = readline(0);
		if (!buff)
			return (-1);
		ret = handle_buff(&data, &buff, env);
		if (ret)
			ft_return(ret, &data, &buff);
		unsigned int i = 0;
		printf("/°\\_/°\\_/°\\_/°\\ Parser Output /°\\_/°\\_/°\\_/°\\\n\n");
		while (i < data.nb_parsed)
		{
			printf("%d = %d %d %s\n", i, data.parsed[i].type, data.parsed[i].size, data.parsed[i].token);
			i++;
		}
		printf("______________________________________________________\n");

		ret = parsing(&data);
		if (ret)
			return (ret);
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
				if (tmp->in)
					close(tmp->in);
				if (tmp->out)
					close(tmp->out);
	
				tmp = tmp->next;
			}
		}	
		ret = execution(&data);
		if (ret)
			return (ret);
		freeer(&data);
	}
	return(0);
}
