#include "../../includes/minishell.h"

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
	token.size = ft_strlen(token.token);
	if (get_parsed(data, token))
	{
		free(token.token);
		return (-1);
	}
	free(token.token);
	return (0);
} 

int	is_env_2(unsigned int *i, t_env *data, char **env)
{
	int	y;

	if (is_char_env(data->lexed[*i + 1].token[0]))
	{
		get_env_var(env, &(data->lexed[*i + 1].token));
		if (data->lexed[*i + 1].token == NULL)
		{
			*i = *i + 1;
			return (1);
		}
	}
	else if (ft_cmp(data->lexed[*i + 1].token, ""))
	{
		*i = *i + 1;
		return (1);
	}
//	else if (data->lexed[*i + 1].token[0] == '?')(voir avec chef comment stocker ca et ou et garder si c simple quote)
	else
	{
		data->lexed[*i].type = STR;
		y = *i + 1;
		while (data->lexed[*i + y].type == ENV)//reparer
			data->lexed[*i + y++].type = STR;//reparer
		if (is_str(i, data))
			return (-1);
		return (1);
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
	if (ret < 0)
		return (ret);
	if (ret == 1)
		return (0);
	data->lexed[*i + 1].type = STR;
	if (data->nb_token > 1 && get_parsed(data, data->lexed[*i + 1]))
		return (-1);
	*i = *i + 1;
	return (0);
}
