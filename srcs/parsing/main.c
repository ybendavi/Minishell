/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:17:23 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/29 22:06:24 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_buff(t_env *data, char **buff)
{
	int	ret;

	ret = lexer(*buff, data);
	if (ret)
	{
		free(*buff);
		*buff = NULL;
		return (ft_return(ret, data));
	}
	ret = init_parser(data, data->env);
	if (ret)
		return (ft_return(ret, data));
	add_history(*buff);
	free(*buff);
	*buff = NULL;
	return (0);
}

void	reset(t_env *data)
{
	set_null(data);
}

void	main_error(t_env *data)
{
	freeer(&data);
	free_lexed(&data);
	free_parsed(&data);
}

int	handle_exec(t_env *data)
{
	int	ret;

	ret = parsing(&data);
	if (ret == -1)
		return (ft_return(-1, data));
	data.status_code = execution(&data);
	if (data.status_code == -1)
		return (ft_return(-1, data));
	freeer(&data);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_env	data;
	char	*buff;

	(void)ac;
	(void)av;
	if (ft_init(&data, env))
		ft_return(1, &data);
	while (7)
	{
		buff = readline("minishell$ ");
		if (!buff)
			ft_return(1, &data);
		data.status_code = handle_buff(&data, &buff);
		if (!data.status_code)
			handle_exec(data);
		else
			main_error(data);
		reset(&data);
	}
	return (0);
}
