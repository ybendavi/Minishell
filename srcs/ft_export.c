/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:58:50 by ccottin           #+#    #+#             */
/*   Updated: 2022/06/26 20:10:12 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_w_export(t_env *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("export %s\n", env[i]);
		i++;
	}
	return (0);
}

int	is_good_str(char *str)
{
	int	i;

	i = 0;
	if (!is_char_env(str[i])
		return (1);
	i++;
	while (str[i] && is_str_env(str[i]))
		i++;
	if (str[i] == '=')
		return (0);
	else if (str[i] == 0)
		return (2);
	else
		return (1);
}

int	not_valid(char *str)
{
	write(2, "bash: export: `", 16);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

//on peut export plusieurs variables en meme temps
int	ft_export(char **strs, t_env *data)
{
	int	i;
	int	ret;

	i = 1;
	if (!strs[i])
		return (print_env_w_export(data));
	while (strs[i])
	{
		ret = is_good_str(strs[i]);
		if (ret == 2)
			return (0);
		if (ret == 1)
			return (not_valid(strs[i]));
	/*TO DO*/
	/*malloc l'environnement, aussi un freer, faire les fonctions de realoc d env*/
}
