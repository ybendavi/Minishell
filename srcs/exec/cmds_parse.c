/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:42:14 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/08 14:37:21 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_size(t_token *token, t_cmds *c_tbls)
{	
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i].type == STR && token[i].token != NULL)
		i++;
	while (c_tbls->cmds[j])
		j++;
	return (i + j);
}

int	set_other_args(t_cmds *c_tbls, t_token *token)
{
	int		i;
	int		j;
	char	**tmp;

	j = 0;
	i = 0;
	if (token[0].type != STR || token[0].token == NULL)
		return (0);
	tmp = ft_calloc(sizeof(char *) * (args_size(token, c_tbls) + 1));
	while (c_tbls->cmds[i])
	{
		tmp[i] = c_tbls->cmds[i];
		i++;
	}
	while (token[j].type == STR && token[j].token != NULL)
	{
		tmp[i] = ft_strdup(token[j].token);
		i++;
		j++;
	}
	if (c_tbls->cmds)
		free(c_tbls->cmds);
	c_tbls->cmds = tmp;
	return (j);
}

int	set_cmds(t_cmds *c_tbls, t_token *token)
{
	int	size;
	int	i;

	i = 0;
	if (c_tbls->cmds)
		return (set_other_args(c_tbls, token));
	size = cmds_len(c_tbls, token);
	if (size == 0)
		return (0);
	if (size == -1)
		return (-1);
	while (i < size && token[i].token != NULL)
	{
		c_tbls->cmds[i] = ft_strdup(token[i].token);
		i++;
	}
	c_tbls->cmds[i] = 0;
	c_tbls->cmd = ft_strdup(c_tbls->cmds[0]);
	return (i);
}
