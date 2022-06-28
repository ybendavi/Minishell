#include "minishell.h"

int	ft_cd_no_args(t_env *envs)
{
	int	i;

	i = 0;
	if (envs->env)
	{
		while (envs->env[i] && ft_strnstr(envs->env[i], "HOME=", 5) == NULL)
			i++;
		if (ft_strnstr(envs->env[i], "HOME=", 5) != NULL)
		{
			if (envs->cupath)
				free(envs->cupath);
			envs->cupath = ft_strdup(&(ft_strchr(envs->env[i], '=')[1]));
			if (chdir(envs->cupath) == -1)
				perror(envs->cupath);
			printf("cupath:%s\n", envs->cupath);
		}
		else
		{
			write(2, "bash: cd: HOME not set\n", ft_strlen("bash: cd: HOME not set\n"));
			return (1);
		}
	}
	return (0);
}

//int	ft_cd(char **args, t_env *envs)
//{
//	i
	
int	cd_main(char **av, t_env *envs)
{
	int	i;

	i = 0;
	printf("ca va\n");
	if (av)
	{
		while (av[i])
			i++;
		if (i > 2)
		{
			write(2, "bash: cd: too many arguments\n", ft_strlen("bash: cd: too many arguments\n"));
			return (1);
		}
		if (i == 1)
			return (ft_cd_no_args(envs));
		if (i == 2)
		{
			if (chdir(av[1]) == -1)
			{
				perror(av[1]);
				return (1);
			}
			return (0);
		}
	}
	return (0);
	//return (ft_cd(av, envs));
}
