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
	if (ft_strcmp(cmds->cmd, "echo") == 0 || ft_strcmp(cmds->cmd, "cd") == 0
		|| ft_strcmp(cmds->cmd, "pwd") == 0 || ft_strcmp(cmds->cmd, "export") == 0
		|| ft_strcmp(cmds->cmd, "unset") == 0 || ft_strcmp(cmds->cmd, "env") == 0
		|| ft_strcmp(cmds->cmd, "exit") == 0)
		return (0);
	else
		return (1);
}

int    builtins(t_cmds *cmds, char **env, t_env *envs)
{
	int	ret;

	(void)env;
	ret = 0;
	if (ft_strcmp(cmds->cmd, "cd") == 0 && cmds->pfd_in[0] == -1 && cmds->pfd_out[0] == -1)
		ret = cd_main(cmds->cmds, envs);
	if (ft_strcmp(cmds->cmd, "pwd") == 0)
		ret = pwd_main(envs);
	if (ft_strcmp(cmds->cmd, "export") == 0)
		ret = ft_export(cmds->cmds, envs);
	if (ft_strcmp(cmds->cmd, "unset") == 0)
		ret = ft_unset(cmds->cmds, envs);
	if (ft_strcmp(cmds->cmd, "env") == 0)
		ret = ft_env(envs, cmds->cmds);
	if (ft_strcmp(cmds->cmd, "exit") == 0 && cmds->pfd_in[0] == -1 && cmds->pfd_out[0] == -1)
		ret = ft_exit(envs, cmds->cmds);
	if (ft_strcmp(cmds->cmd, "echo") == 0)
		ret = ft_echo(cmds->cmds);
	if (ft_strcmp(cmds->cmd, "cd") && ft_strcmp(cmds->cmd, "exit"))
	{
		freeer(envs);
		free_lexed(envs);
		free_parsed(envs);
		free_all(envs);
		rl_clear_history();
	}
	return (ret);
}
