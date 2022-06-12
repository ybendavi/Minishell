/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:03:51 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/01 19:05:55 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	main(int ac, char **av, char **env)
{
	unsigned int	i;
	t_env	data;
	int	ret;
	char 	*buff;

	(void)ac;
	(void)av;
//	(void)env;
	if (ft_init(&data))
		return(ft_return(-1, &data, NULL));
	while (7)
	{
		buff = readline(0);
		if (!buff)
			return (-1);
		if (ft_cmp(buff, "exit") == 1)
			return (ft_return(0, &data, &buff));
		ret = lexer(buff, &data);
		if (ret != 0)
			return (ft_return(ret, &data, &buff));
		free(buff);
		buff = NULL;
/* lexer tester	*/	
		i = 0;
		printf("/°\\_/°\\_/°\\_/°\\ Lexer Output /°\\_/°\\_/°\\_/°\\\n\n");
		while (i < data.nb_token)
		{
			printf("%d = %d %d %s\n", i, data.lexed[i].type, data.lexed[i].size, data.lexed[i].token);
			i++;
		}
	//	free_lexed(&data);
		ret = init_parser(&data, env);
		if (ret)
			return (ft_return(ret, &data, &buff));
		ret = check_parsing_errors(&data);
		if (ret)
			return (ft_return(ret, &data, &buff));
		i = 0;
		printf("/°\\_/°\\_/°\\_/°\\ Parser Output /°\\_/°\\_/°\\_/°\\\n\n");
		while (i < data.nb_parsed)
		{
			printf("%d = %d %d %s\n", i, data.parsed[i].type, data.parsed[i].size, data.parsed[i].token);
			i++;
		}
		printf("______________________________________________________\n");
		free_parsed(&data);
	}
	return (0);
}
