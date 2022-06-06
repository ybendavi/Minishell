/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:49:03 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/06 21:34:41 by ccottin          ###   ########.fr       */
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

int	get_parsed(t_env *data, t_token token)
{
	printf("%d\n", token.type);
	if (token.type == WHITE_SPACE)
	{
		free(data->parsed[data->nb_parsed].token);
		data->parsed[data->nb_parsed].token = ft_cpy2(" ");
	}
	else
		data->parsed[data->nb_parsed].token = ft_cpy2(token.token);
	if (!data->parsed[data->nb_parsed].token)
		return (-1);
	data->parsed[data->nb_parsed].size = token.size;
	data->parsed[data->nb_parsed].type = token.type;
	data->nb_parsed++;
	return (0);
}

int	is_redir(unsigned int i, t_env *data)
{
	if (i == 0)
	{
		if (get_parsed(data, data->lexed[i]))
			return (-1);
	}
	else if (data->parsed[data->nb_parsed - 1].type != PIPE
		&& data->parsed[data->nb_parsed - 1].type != STR
		&& data->parsed[data->nb_parsed - 1].type != ENV
		&& data->parsed[data->nb_parsed - 1].type != QUOTE)
		return (-3);
	else
	{
		if (get_parsed(data, data->lexed[i]))
			return (-1);
	}
	return (0);
}

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
/*
int	check_var_env(t_token *token, char **env)
{
	int	i;

	i = 0;
	while (token->token[i])
	{
		if (token->token[i] == '$') //gerer aussi $?
		{
			
		}
	}
}

int	is_str(unsigned int i, t_env *data)
{
	while (data->lexed[*i].type == QUOTE)
	{
		if (data->lexed[*i].token[0] != '\'')
		{
			if (check_var_env(&(data->lexed[*i]), env) == -1)
				return (-1);
		}
		
	}
	if (get_parsed(data, data->lexed[*i]))
		return (-1);
}*/

int	is_whitespace(unsigned int *i, t_env *data) //le segfault vient de laaaaa
{
	while (data->lexed[*i].type == WHITE_SPACE)
		*i = *i + 1;
	if (get_parsed(data, data->lexed[*i]))
		return (-1);
	return (0);
}

int	is_char_env(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

void	get_env_var(char **env, char **var)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i] && ft_strnstr(env[i], *var, ft_strlen(*var)) == NULL)
		i++;
	if (env[i] == NULL)
	{
		*var = NULL;
		return ;
	}
	str = ft_strchr(env[i], '=');
	free(*var);
	*var = &str[1];
	*var = ft_cpy2(*var);
}

int	is_env(unsigned int *i, t_env *data, char **env)
{
	printf("i = %d\n", *i);
	if (data->nb_token <= *i + 1)
	{
		data->lexed[*i].type = STR;
		if (get_parsed(data, data->lexed[*i]))
			return (-1);
		return (0);
	}
	if (is_char_env(data->lexed[*i + 1].token[0]))
	{
		get_env_var(env, &(data->lexed[*i + 1].token));
		if (data->lexed[*i + 1].token == NULL)
		{
			*i = *i + 1;
			return (0);
		}
	}
	else
	{
		data->lexed[*i].type = STR;
		if (get_parsed(data, data->lexed[*i]))
			return (-1);
	}
	data->lexed[*i + 1].type = STR;
	if (data->nb_token > 1 && get_parsed(data, data->lexed[*i + 1]))
		return (-1);
	*i = *i + 1;
	return (0);
}

int	check_type(unsigned int *i, t_env *data, char **env)
{
	if (data->lexed[*i].type == WHITE_SPACE)
		return (is_whitespace(i, data));
	if (data->lexed[*i].type == REDIR_ADD
		|| data->lexed[*i].type == REDIR_LIM
		|| data->lexed[*i].type == REDIR_IN 
		|| data->lexed[*i].type == REDIR_OUT)
		return (is_redir(*i, data));
	else if (data->lexed[*i].type == PIPE)
		return (is_pipe(*i, data));
	else if (data->lexed[*i].type == ENV)
		return (is_env(i, data, env));
	else if (data->lexed[*i].type == STR || data->lexed[*i].type == QUOTE)
	{
		if (get_parsed(data, data->lexed[*i]))
			return (-1);
	}
	//	is_str(i, data, env);
	return (0);
}

int	init_parser(t_env *data, char **env)
{
	unsigned int	i;

	i = 0;
	data->nb_parsed = 0;
	data->parsed = ft_calloc(100 * sizeof(t_token));
	if (!data->parsed)
		return (-1);
	while (i < data->nb_token)
	{
		if (check_type(&i, data, env))
		{
			data->error = data->lexed[i].token;
			return (-3);
		}
		i++;
	}
	free_lexed(data);
	return (0);
}
