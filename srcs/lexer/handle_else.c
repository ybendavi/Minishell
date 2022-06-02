/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_else.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:13:31 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/02 23:16:05 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	handle_pipe(char **temp, t_env *env)
{
	if (check_temp(temp, env))
		return (-1);
	if (get_lexed(ft_cpy(temp, "|"), env, PIPE))
		return (-1);
	return (0);
}

int	is_double_redir(char r, char **temp, t_env *env)
{
	if (r == '>')
	{
		if (get_lexed(ft_cpy(temp, ">>"), env, REDIR_ADD))
			return (-1);
	}
	if (r == '<')
	{
		if (get_lexed(ft_cpy(temp, "<<"), env, REDIR_LIM))
			return (-1);
	}
	return (1);
}

int	handle_redir(char *line, int *i, char **temp, t_env *env)
{
	char	r;

	if (check_temp(temp, env))
		return (-1);
	r = line[*i];
	if (line[*i + 1] == r)
	{
		*i = *i + 1;
		return (is_double_redir(line[*i], temp, env));
	}
	else if (line[*i] == '>')
	{
		if (get_lexed(ft_cpy(temp, ">"), env, REDIR_IN))
			return (-1);
	}
	else if (line[*i] == '<')
	{
		if (get_lexed(ft_cpy(temp, "<"), env, REDIR_IN))
			return (-1);
	}
	return (0);
}

//si on en abesoin, ici rajouter une decoupe des whitespace char par char un peu comme le tableau de token
int	handle_white_space(int *i, char *line, char **temp,
		t_env *env)
{
	int	start;
	
	if (check_temp(temp, env))
		return (-1);
	start = *i;
	while (line[*i] == ' ' || line[*i] == '\r' || line[*i] == '\t'
		|| line[*i] == '\n' || line[*i] == '\v' || line[*i] == '\f')
		*i = *i + 1;
	if (start != *i)
	{
		if (get_lexed(ft_cpy(temp, " "), env, WHITE_SPACE))
			return (-1);
	}
	*i = *i - 1;
	return (0);
}
