

int	child_process(t_cmds *cmd, char **env)
{
	if (cmd->pfd_in[0] != -1)
	{
		if (close(pfd_in[1]) != 0)
			perror("e");
		if (dup2(pfd_in[0], 0) == -1)
			perror("o");
		if (close(pfd_in[0]))
			perror("a");
	}
	if (cmd->pfd_out[0] != -1)
	{
		if (close(pfd_out[0]) != 0)
			perror("e");
		if (dup2(pfd_out[1], 1) == -1)
			perror("o");
		if (close(pfd_out[1]))
			perror("a");
	}
	if (cmd->in != 0 && cmd->in != pfd_in[0])
	{
		if (dup2(cmd_in, 0) == -1)
			perror("coucou");
	}
	if (cmd->out != 0 && cmd->out != pfd_out[1])
	{
		if (dup2(cmd_out, 1) == -1)
			perror("coucou");
	}
	execve(cmd->cmds[0], cmd->cmds, env);
}
