/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:24:47 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/06 21:01:25 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init(t_env *data, char **temp)
{
	data->nb_token = 0;
	data->lexed = ft_calloc(sizeof(t_token) * 100);//DYMANIQUE
	if (!data->lexed)
		return (-1);
	*temp = ft_calloc(1024);
	if (!temp)
		return (-1);
	return (0);
}

int	get_lexed(char **temp, t_env *data, t_token_type type)
{
	int	y;

	data->lexed[data->nb_token].size = ft_strlen(*temp);
	data->lexed[data->nb_token].type = type;
	data->lexed[data->nb_token].token
		= ft_calloc(data->lexed[data->nb_token].size + 1);
	if (!data->lexed[data->nb_token].token)
		return (-1);
	y = 0;
	while ((*temp)[y])
	{
		data->lexed[data->nb_token].token[y] = (*temp)[y];
		(*temp)[y] = 0;
		y++;
	}
	data->nb_token++;
	return (0);
}

void	add_temp(char *line, int *i, char **temp)
{
	int	y;

	y = 0;
	while ((*temp)[y])
		y++;
	(*temp)[y] = line[*i];
}

int	lexer2(char *line, char **temp, int *i, t_env *data)
{
	if (line[*i] == '|')
		return (handle_pipe(temp, data));
	else if (line[*i] == '>' || line[*i] == '<')
		return (handle_redir(line, i, temp, data));
	else if (line[*i] == '\'' || line[*i] == '"')
		return (handle_quote(line, i, temp, data));
	else if (line[*i] == ' ' || line[*i] == '\r' || line[*i] == '\t'
		|| line[*i] == '\n' || line[*i] == '\v' || line[*i] == '\f')
		return (handle_white_space(i, line, temp, data));
	else if (line[*i] == '$')
		return (handle_env(temp, data));
	else
		add_temp(line, i, temp);
	return (0);
}

int	lexer(char *line, t_env *data)
{
	char	*temp;
	int		i;
	int		ret;

	if (init(data, &temp) == -1)
		return (-1);
	i = 0;
	ret = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		line[i] = 0;
	i = 0;
	while (line[i])
	{
		ret = lexer2(line, &temp, &i, data);
		if (ret < 0)
		{
			free(temp);
			return (ret);
		}
		i++;
	}
	if (ft_strlen(temp) != 0)
		get_lexed(&temp, data, STR);
	free(temp);
	return (0);
}

void	free_lexed(t_env *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_token)
	{
		if (data->lexed[i].token)
			free(data->lexed[i].token);
		i++;
	}
	if (data->lexed)
		free(data->lexed);
}

void	free_parsed(t_env *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nb_parsed)
	{
		if (data->parsed[i].token)
			free(data->parsed[i].token);
		i++;
	}
	if (data->parsed)
		free(data->parsed);
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
	while (i < 12)
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
	return (-1);
}

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
	size_t	size;

	(void)ac;
	(void)av;
	if (token_init(&data) == -1)
		return (ft_return(-1, &data, NULL));
	buff = ft_calloc(2048);
	if (!buff)
		return (ft_return(-1, &data, NULL));
	size = 2048;
	while (7)
	{
		getline(&buff, &size, stdin);
		if (ft_cmp(buff, "exit\n") == 1)
			return (ft_return(0, &data, &buff));
		ret = lexer(buff, &data);
		if (ret != 0)
			return (ft_return(ret, &data, &buff));
		i = 0;
		ret = init_parser(&data, env);
		if (ret) //on peut free buffer ici
			return (ft_return(ret, &data, &buff));
		ret = check_parsing_errors(&data);
		if (ret)
			return (ft_return(ret, &data, &buff));
		while (i < data.nb_parsed)
		{
			printf("%d = %d %d %s\n", i, data.parsed[i].type, data.parsed[i].size, data.parsed[i].token);
			i++;
		}
		free_parsed(&data);
	/*	while (i < 11)
		{
			printf("%d = %d %d %s\n", i, data.tab[i].type, data.tab[i].size, data.tab[i].token);
			i++;
		}*/
	}
	return (0);
}
