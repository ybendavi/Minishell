/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:34:36 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/30 18:41:12 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_main(t_env *envs)
{
	char	*path;

	(void)envs;
	path = ft_calloc(sizeof(char) * 1000);
	getcwd(path, 999);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	return (0);
}
