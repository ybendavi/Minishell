/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:17:23 by ccottin           #+#    #+#             */
/*   Updated: 2022/07/10 23:25:48 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

int	handle_buff(t_env *data, char **buff)
{
	int	ret;

	if (ft_strncmp(*buff, "", ft_strlen(*buff)))
		add_history(*buff);
	ret = lexer(*buff, data, 0);
	if (ret)
	{
		free(*buff);
		*buff = NULL;
		return (ft_return(ret, data));
	}
	free(*buff);
	*buff = NULL;
	ret = init_parser(data);
	if (ret)
		return (ft_return(ret, data));
	return (0);
}

void	reset(t_env *data)
{
	set_null(data);
}

void	main_error(t_env *data)
{
	freeer(data);
	free_lexed(data);
	free_parsed(data);
}

int	handle_exec(t_env *data)
{
	int	ret;

	ret = parsing(data);
	if (ret == -1)
		return (ft_return(-1, data));
	data->status_code = execution(data);
	if (data->status_code == -1)
		return (ft_return(-1, data));
	freeer(data);
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
			handle_exec(&data);
		else
			main_error(&data);
		reset(&data);
	}
	return (0);
}
