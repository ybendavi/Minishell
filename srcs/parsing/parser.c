#include "minishell.h"

int	get_env_var(char **env, char **var)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i] && ft_env_strnstr(env[i], *var, ft_strlen(*var)) == NULL)
		i++;
	if (env[i] == NULL)
	{
		if (*var)
			free(*var);
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

char	*ft_concat(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		y;

	if (!s1)
		ret = ft_calloc(ft_strlen(s2) + 1);
	else
		ret = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
	}
	y = 0;
	while (s2[y])
		ret[i++] = s2[y++];
	if (s1)
		free(s1);
	return (ret);
}

int	is_str(unsigned int *i, t_env *data)
{
	t_token	token;

	token.token = NULL;
	while (data->lexed[*i].type == STR)
	{
		token.token = ft_concat(token.token, data->lexed[*i].token);
		if (!token.token)
			return (-1);
		*i = *i + 1;
	}
	*i = *i - 1;
	token.type = STR;
	if (get_parsed(data, token))
	{
		free(token.token);
		return (-1);
	}
	free(token.token);
	return (0);
} 

//	else if (data->lexed[*i + 1].token[0] == '?')(voir avec chef comment stocker ca et ou et garder si c simple quote)

t_token	struct_env(char *str, int type)
{
	t_token	token;

	token.token = str;
	token.type = type;
	return (token);
}

int	is_env(unsigned int *i, t_env *data, char **env)
{
	unsigned int	y;
	char	*str;
	
	y = *i;
	str = NULL;
	while (data->lexed[y].type == ENV)
	{
		if (data->nb_token <= y + 1)
		{
			str = ft_concat(str, "$");
			if (!str)
				return (-1);
			y++; //??
		}
		else if (data->lexed[y].token[1] == '"'
			|| data->lexed[y].token[1] == '\'')
		{
			str = ft_concat(str, data->lexed[y + 1].token);
			if (!str)
				return (-1);
		}
		else if (is_char_env(data->lexed[y].token[1]))
		{
			if (get_env_var(env, &(data->lexed[y + 1].token)))
				return (-1);
			if (data->lexed[y + 1].token)
			{
				str = ft_concat(str, data->lexed[y + 1].token);
				if (!str)
					return (-1);
			}
		
		}
		else
		{
			if (data->lexed[y + 1].type != STR && data->lexed[y + 1].type != ENV)
			{
				str = ft_concat(str, "$");
				if (!str)
					return (-1);
				str = ft_concat(str, data->lexed[y + 1].token);
				if (!str)
					return (-1);
			}
			if (data->lexed[y + 1].type == ENV)
			{
				str = ft_concat(str, "$$");
				if (!str)
					return (-1);
			}

		}
		y = y + 2;
	}
	*i = y - 1;
	if (data->nb_parsed > 0 && data->parsed[data->nb_parsed - 1].type == STR)
	{
		if (str)
		{
			data->parsed[data->nb_parsed - 1].token =
			ft_concat(data->parsed[data->nb_parsed - 1].token, str);
			if (!data->parsed[data->nb_parsed - 1].token)
				return (-1);
			data->parsed[data->nb_parsed - 1].size
			= ft_strlen(data->parsed[data->nb_parsed - 1].token);
		}
		else
		{
			if (get_parsed(data, struct_env("", STR)))
				return (-1);
		}
	}
	else
	{
		if (str)
		{
			if (get_parsed(data, struct_env(str, STR)))
				return (-1);
		}
	}
	if (str)
		free(str);
	return (0);
}
