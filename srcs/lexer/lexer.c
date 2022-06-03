/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 22:24:47 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/03 15:51:44 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init(t_env *env, char **temp)
{
	env->nb_token = 0;
	env->lexed = ft_calloc(sizeof(t_token) * 100);
	if (!env->lexed)
		return (-1);
	*temp = ft_calloc(1024);
	if (!temp)
		return (-1);
	return (0);
}

int	get_lexed(char **temp, t_env *env, t_token_type type)
{
	int	y;

	env->lexed[env->nb_token].size = ft_strlen(*temp);
	env->lexed[env->nb_token].type = type;
	env->lexed[env->nb_token].token
		= ft_calloc(env->lexed[env->nb_token].size + 1);
	if (!env->lexed[env->nb_token].token)
		return (-1);
	y = 0;
	while ((*temp)[y])
	{
		env->lexed[env->nb_token].token[y] = (*temp)[y];
		(*temp)[y] = 0;
		y++;
	}
	env->nb_token++;
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

int	lexer2(char *line, char **temp, int *i, t_env *env)
{
	if (line[*i] == '|')
		return (handle_pipe(temp, env));
	else if (line[*i] == '>' || line[*i] == '<')
		return (handle_redir(line, i, temp, env));
	else if (line[*i] == '\'' || line[*i] == '"')
		return (handle_quote(line, i, temp, env));
	else if (line[*i] == ' ' || line[*i] == '\r' || line[*i] == '\t'
		|| line[*i] == '\n' || line[*i] == '\v' || line[*i] == '\f')
		return (handle_white_space(i, line, temp, env));
	else
		add_temp(line, i, temp);
	return (0);
}

int	lexer(char *line, t_env *env)
{
	char	*temp;
	int		i;
	int		ret;

	if (init(env, &temp) == -1)
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
		ret = lexer2(line, &temp, &i, env);
		if (ret < 0)
		{
			free(temp);
			return (ret);
		}
		i++;
	}
	if (ft_strlen(temp) != 0)
		get_lexed(&temp, env, STR);
	free(temp);
	return (0);
}

void	free_lexed(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_token)
	{
		if (env->lexed[i].token)
			free(env->lexed[i].token);
		i++;
	}
	if (env->lexed)
		free(env->lexed);
}

int	ft_return(int ret, t_env *env, char **buff)
{
	unsigned int	i;

	if (*buff)
		free(*buff);
	i = 0;
	while (i < 11)
	{
		if (env->tab[i].token)
			free(env->tab[i].token);
		i++;
	}
	if (env->tab)
		free(env->tab);
	if (ret != 0)
		free_lexed(env);
	if (ret == -1)
		write(2, "Malloc error.\n", 14);
	if (ret == -2)
		write(1, "Lone quote.\n", 12);
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

int	main(void)
{
	unsigned int	i;
	t_env	env;
	int	ret;
	char 	*buff;
	size_t	size;

	if (token_init(&env) == -1)
		return (ft_return(-1, &env, NULL));
	buff = ft_calloc(2048);
	if (!buff)
		return (ft_return(-1, &env, NULL));
	size = 2048;
	while (7)
	{
		getline(&buff, &size, stdin);
		if (ft_cmp(buff, "exit\n") == 1)
			return (ft_return(0, &env, &buff));
		ret = lexer(buff, &env);
		if (ret != 0)
			return (ft_return(ret, &env, &buff));
		i = 0;
		ret = init_parser(&env);
		if (ret) //on peut free buffer ici
			return (ft_return(ret, &env, &buff));
		while (i < env.nb_token)
		{
			printf("%d = %d %d %s\n", i, env.lexed[i].type, env.lexed[i].size, env.lexed[i].token);
			i++;
		}
		free_lexed(&env);
	/*	while (i < 11)
		{
			printf("%d = %d %d %s\n", i, env.tab[i].type, env.tab[i].size, env.tab[i].token);
			i++;
		}*/
	}
	return (0);
}
