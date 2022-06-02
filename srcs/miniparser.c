#include "minishell.h"

int	new_fd(char *filename, t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT)
		return (open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666 | O_TRUNC));
	else
		return (open(filename, O_RDWR | O_APPEND));
	return (0);
}

int	*new_pfd(void)
{
	int	*pipe;

	pipe = malloc(sizeof(int) * 2);
	if (!pipe)
		return (0);
	return (pipe);
}

t_token_type	choose_tok(char *str)
{
	if (ft_strncmp(">", str, ft_strlen(str)) == 0)
		return (REDIR_IN);	
	if (ft_strncmp("<", str, ft_strlen(str)) == 0)
		return (REDIR_OUT);	
	if (ft_strncmp(">>", str, ft_strlen(str)) == 0)
		return (REDIR_ADD);	
	if (ft_strncmp("<<", str, ft_strlen(str)) == 0)
		return (REDIR_LIM);
	if (ft_strncmp("|", str, ft_strlen(str)) == 0)
		return (PIPE);
	return (0);
}

int	set_fd(t_cmds *c_tbls, char **strs)
{
	if (choose_tok(strs[0]) == REDIR_IN || choose_tok(strs[0]) == REDIR_ADD)
		c_tbls->out = new_fd(strs[1], choose_tok(strs[0]));
	else
		c_tbls->in = new_fd(strs[1], choose_tok(strs[0]));
	return (0);
}

int	cmds_len(t_cmds *c_tbls, char **strs)
{	

	int	i;
	
	i = 0;
	while (strs[i] && choose_tok(strs[i]) == 0)
		i++;
	if (i == 0)
		c_tbls->cmds = NULL;
	else
	{
		c_tbls->cmds = malloc(sizeof(char *) * (i + 1));
		if (!c_tbls->cmds)
			return (-1);
	}
	return (i);
}

int	set_cmds(t_cmds *c_tbls, char **strs)
{
	int	size;
	int	i;

	i = 0;
	if (c_tbls->cmds)
		return (0);
	size = cmds_len(c_tbls, strs);
	if (size == 0)
		return (0);
	if (size == -1)
		return (-1);
	while (i < size)
	{
		c_tbls->cmds[i] = ft_strdup(strs[i]);
		i++;
	}
	c_tbls->cmds[i] = 0;
	c_tbls->cmd = ft_strdup(strs[0]);
	return (i);
}

int	new_table(t_env *envs)
{
	t_cmds	*tmp;

	tmp = envs->c_tbls;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_cmds) * 1);
		if (!tmp->next)
			return (-1);
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	else
	{
		tmp = malloc(sizeof(t_cmds) * 1);
		if (!tmp)
			return (-1);
		envs->c_tbls = tmp;
	}
	tmp->cmds = NULL;
	tmp->cmd = NULL;
	tmp->in = 0;
	tmp->out = 1;
	tmp->next = NULL;
	tmp->pfd = malloc(sizeof(int) * 2);
	tmp->pfd[0] = -1;
	if (!envs->c_tbls || !tmp)
		return (-1);
	return (0);
}

int	redir_parse(t_env *envs, char **strs)
{
	int	i;
	t_cmds	*tmp;

	i = 0;
	tmp = envs->c_tbls;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	else
	{
		if (new_table(envs) == -1)
			return (-1);
		tmp = envs->c_tbls;
	}
	set_fd(tmp, strs);
	i = 1 + set_cmds(tmp, &strs[2]);
	return (i);
}

int	pipe_parse(t_env *envs, char **strs)
{
	t_cmds	*tmp;
	int	i;

	i  = 0;
	tmp = envs->c_tbls;
	while (tmp->next)
		tmp = tmp->next;
	new_table(envs);
	if (pipe(tmp->pfd) == -1)
		return (-1);
	tmp->out = tmp->pfd[1];
	tmp->next->pfd = tmp->pfd;
	tmp->next->in = tmp->next->pfd[0];
	tmp = tmp->next;
	i = set_cmds(tmp, &strs[1]);
	return (i);
}



int	recu_parse(t_env *envs, char **strs)
{
	int	i;

	if (ft_strncmp(">", *strs, ft_strlen(*strs)) == 0
			|| ft_strncmp("<", *strs, ft_strlen(*strs)) == 0
			|| ft_strncmp(">>", *strs, ft_strlen(*strs)) == 0
			|| ft_strncmp("<<", *strs, ft_strlen(*strs)) == 0)
		{
			i = redir_parse(envs, strs);
			if (i == -1)
				return (-1);
			if (strs[i] && strs[i + 1])
			{
				if (recu_parse(envs, &strs[i + 1]) == -1)
					return (-1);
			}
		}
	if (ft_strncmp("|", *strs, ft_strlen(*strs)) == 0)
	{
		i = pipe_parse(envs, strs);
		if (i == -1)
			return (-1);
		if (strs[i] && strs[i + 1])
		{
			if (recu_parse(envs, &strs[i + 1]) == -1)
				return (-1);
		}
	}
	return (0);
}


void	parsing(t_env *envs, char *av)
{
	int	i;
	char	**strs;

	strs = ft_split(av, ' ');
	envs->c_tbls = NULL;
	i = 0;
	if (choose_tok(*strs) == 0)
	{
		new_table(envs);
		i = set_cmds(envs->c_tbls, strs);
	}
	recu_parse(envs, &strs[i]);
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;

	}
	free(strs);

}
