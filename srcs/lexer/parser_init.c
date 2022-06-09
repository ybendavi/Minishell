/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:49:03 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/07 20:54:04 by ccottin          ###   ########.fr       */
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
/**env**/

int	ft_mcpy(char *s1, char **s2)
{
	int	i;

	i = 0;
	*s2 = ft_calloc(ft_strlen(s1) + 1);
	if (!*s2)
		return (-1);
	while (s1[i])
	{
		(*s2)[i] = s1[i];
		i++;
	}
	return (0);
}

int	is_char_env(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	get_env_var(char **env, char **var)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i] && ft_env_strnstr(env[i], *var, ft_strlen(*var)) == NULL)
		i++;
	if (env[i] == NULL)
	{
		*var = NULL;
		return (0);
	}
	str = ft_strchr(env[i], '=');
	if (*var)
		free(*var);
	if (ft_mcpy(&str[1], var))
		return (-1);
	return (0);
}

int	parse_str(t_env *data, char *str, int start, int end)
{
	t_token	token;
	int	i;

	token.token = ft_calloc(end - start + 1);
	if (!token.token)
		return (-1);
	i = 0;
	while (i < end - start)
	{
		token.token[i] = str[start + i];
		i++;
	}
	token.type = STR;
	token.size = ft_strlen(token.token);
	if (get_parsed(data, token))
		return (-1);
	free(token.token);
	return (0);
}

char	*get_str_env(char *token, int j)
{
	char	*ret;
	int		y;
	int		x;
	
	j++;
	y = j;
	while (is_char_env(token[y]))
		y++;
	x = y - j;
	ret = ft_calloc(x + 1);
	if (!ret)
		return (NULL);
	y = 0;
	while (y < x)
	{
		ret[y] = token[j];
		y++;
		j++;
	}
	return (ret);
}

int	get_start(char *token, int end)
{
	int	start;

	start = end;
	while (token[start] && token[start - 1] != '"')
		start--;
	if (start < 0)
		return (0);
	return (start);
}

int	parse_var_env(t_env *data, char **env, char *str)
{
	t_token	token;

	if (!str)
		return (-1);
	if (get_env_var(env, &(str))) 
		return (-1);
	if (str == NULL)
		return (0);
	token.type = STR;
	token.token = str;
	token.size = ft_strlen(str);
	if (get_parsed(data, token))
		return (-1);
	free(str);
	return (0);
}

int	check_var_env(t_token *token, char **env, t_env *data)
{
	int		j;

	j = 0;
	while (token->token[j])
	{
		if (token->token[j] == '$') //gerer aussi $?
		{
			if (is_char_env(token->token[j + 1]))
			{
				if (parse_str(data, token->token, get_start(token->token, j), j))
					return (-1);
				if (parse_var_env(data, env, get_str_env(token->token, j)))
					return (-1);
				j++;
				while (is_char_env(token->token[j]))
					j++;
				token->token[j - 1] = 0;
			}
		}
		j++;
	}
	//lexer toute la partie depuis j--, elle est pas prise en compte
	return (0);
}

int	is_str(unsigned int *i, t_env *data, char **env)
{
	if (data->lexed[*i].type == QUOTE)
	{
		if (data->lexed[*i].token[0] == '"')
		{
			if (remove_quote(&(data->lexed[*i].token)))
				return (-1);
			if (check_var_env(&(data->lexed[*i]), env, data) == -1)
				return (-1);
		}
		else
		{
			if (remove_quote(&(data->lexed[*i].token)))
				return (-1);
			if (get_parsed(data, data->lexed[*i]))
				return (-1);
		}

	}
	else
	{
		if (get_parsed(data, data->lexed[*i]))
			return (-1);
	}
	return (0);
}

int	is_env_2(unsigned int *i, t_env *data, char **env)
{
	if (is_char_env(data->lexed[*i + 1].token[0]))
	{
		get_env_var(env, &(data->lexed[*i + 1].token));
		if (data->lexed[*i + 1].token == NULL)
		{
			*i = *i + 1;
			return (1);
		}
	}
//	else if (data->lexed[*i + 1].token[0] == '?')(voir avec chef comment stocker ca et ou et garder si c simple quote)
	else
	{
		data->lexed[*i].type = STR;
		if (get_parsed(data, data->lexed[*i]))
			return (-1);
	}
	return (0);
}

int	is_env(unsigned int *i, t_env *data, char **env)
{
	int	ret;

	if (data->nb_token <= *i + 1)
	{
		data->lexed[*i].type = STR;
		if (get_parsed(data, data->lexed[*i]))
			return (-1);
		return (0);
	}
	ret = is_env_2(i, data, env);
	if (ret)
		return (ret);
	data->lexed[*i + 1].type = STR;
	if (data->nb_token > 1 && get_parsed(data, data->lexed[*i + 1]))
		return (-1);
	*i = *i + 1;
	return (0);
}
/**endenv**/
int	is_whitespace(unsigned int *i, t_env *data)
{
	while (data->lexed[*i].type == WHITE_SPACE)
		*i = *i + 1;
	*i = *i - 1;
	if (get_parsed(data, data->lexed[*i]))
		return (-1);
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
		is_str(i, data, env);
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
