/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:49:03 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/03 18:47:11 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_cpy2(char *s1)
{
	char	*s2;
	int	i;

	i = 0;
	s2 = ft_calloc(ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

int	get_parsed(t_env *env, t_token token)
{
	env->parsed[env->nb_parsed].token = ft_cpy2(token.token);
	if (!env->parsed[env->nb_parsed].token)
		return (-1);
	env->parsed[env->nb_parsed].size = token.size;
	env->parsed[env->nb_parsed].type = token.type;
	env->nb_parsed++;
	return (0);
}

int	is_redir(unsigned int i, t_env *env)
{
	if (i == 0)
	{
		if (get_parsed(env, env->lexed[i]))
			return (-1);
	}
	else if (env->parsed[env->nb_parsed - 1].type != PIPE
		&& env->parsed[env->nb_parsed - 1].type != STR)
		return (-3);
	else
	{
		if (get_parsed(env, env->lexed[i]))
			return (-1);
	}
	return (0);
}

int	is_pipe(unsigned int i, t_env *env)
{
	if (i == 0)
		return (-3);
	if (env->parsed[env->nb_parsed - 1].type != STR)
		return (-3);
	else
	{
		if (get_parsed(env, env->lexed[i]))
			return (-1);
	}
	return (0);

}
/*
int	is_str(unsigned int i, t_env *env)
{
	c'est l endroit ou on transforme les tokens en cmd, file ou autre si besoin
}
*/

int	check_type(unsigned int *i, t_env *env)
{
	while (env->lexed[*i].type == WHITE_SPACE)
		*i = *i + 1;
	if (env->lexed[*i].type == REDIR_ADD
		|| env->lexed[*i].type == REDIR_LIM
		|| env->lexed[*i].type == REDIR_IN 
		|| env->lexed[*i].type == REDIR_OUT)
		return (is_redir(*i, env));
	else if (env->lexed[*i].type == PIPE)
		return (is_pipe(*i, env));
	else if (env->lexed[*i].type == STR)
	{
	//	is_str(i, env);
		if (get_parsed(env, env->lexed[*i]))
			return (-1);
	}
	return (0);
}

int	init_parser(t_env *env)
{
	unsigned int	i;

	i = 0;
	env->nb_parsed = 0;
	env->parsed = ft_calloc(100 * sizeof(t_token));
	if (!env->parsed)
		return (-1);
	while (i < env->nb_token)
	{
		if (check_type(&i, env))
		{
			env->error = env->lexed[i].token;
			return (-3);
		}
		i++;
	}
	free_lexed(env);
	return (0);
}
