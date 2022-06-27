#include "minishell.h"

void	set_null(t_env *data)
{
	data->lexed = NULL;
	data->parsed = NULL;
	data->error = NULL;
	data->temp = NULL;
	data->nb_token = 0;
	data->nb_parsed = 0;
	data->error = NULL;
	data->temp = NULL;
	data->c_tbls = NULL;
}
/*
int	set_env_i(t_env *data)
{
	char	**ret;
	int	i;

	ret = ft_calloc((sizeof(char *) * 4));
	if (!ret)
		return (-1);
	i = 0;
	ret[i] = PWD;
	i++;
	ret[i] = ft_cpy2("SHLVL=1");
	if (!ret[i])
		return (-1);
	i++;
	ret[i] = _ {chemin absolu pour l env};
	return (0);
}*/

int	env_init(t_env *data, char **env)
{
	int	i;
	char	**new;

	i = 0;
//	if (!data->env[i])
//		return (set_env_i(data));
	while (env[i])
		i++;
	new = ft_calloc((sizeof(char *) * i + 1));
	if (!new)
		return (-1);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (-1);
		if (!ft_strncmp("SHLVL=", new[i], 5))
			new[i][6] = new[i][6] + 1;
		i++;
	}
	data->env = new;
	return (0);
}

int	ft_init(t_env *data, char **env)
{
	int	ret;

	data->tab = NULL;
	set_null(data);
	if (env_init(data, env))
		return (-1);
	if (token_init(data) == -1)
		return (-1);
	ret = signal_init();
	if (ret)
		printf("sigerror, ret = %d\n", ret);
	int i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
