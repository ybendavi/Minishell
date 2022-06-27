#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	is_builtin(t_cmds *cmds)
{
	if (!cmds->cmd)
		return (1);
	if (/*ft_strcmp(cmds->cmd, "echo") == 0 || */ft_strcmp(cmds->cmd, "cd") == 0/*
		|| ft_strcmp(cmds->cmd, "pwd") == 0 || ft_strcmp(cmds->cmd, "export") == 0
		|| ft_strcmp(cmds->cmd, "unset") == 0 || ft_strcmp(cmds->cmd, "env") == 0
		|| ft_strcmp(cmds->cmd, "exit") == 0*/)
		return (0);
	else
		return (1);
}

int	builtins(t_cmds *cmds, char **env, t_env *envs)
{
	int	ret;

	(void)env;
	ret = 0;
	if (ft_strcmp(cmds->cmd, "cd") == 0)
		ret = cd_main(cmds->cmds, envs);
	return (ret);
}
