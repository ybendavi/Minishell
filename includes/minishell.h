/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:46:40 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/03 15:52:27 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

typedef enum e_token_type {
	REDIR_ADD,
	REDIR_LIM,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	WHITE_SPACE,
	STR,
	FLAG,
	CMD
}		t_token_type;

typedef struct s_token {
	char			*token;
	uint32_t		size;
	t_token_type	type;
}	t_token;

typedef struct s_env {
	t_token	*tab;
	t_token	*lexed;
	uint32_t	nb_token;
	uint32_t	size;
}			t_env;

typedef struct command_table_list
{
	char						**cmd;
	int							in;
	int							out;
	struct command_table_list	*next;
}					t_cmds;

void	*ft_calloc(size_t nmem);
char	**ft_cpy(char **temp, char *s1);
size_t	ft_strlen(char *str);
int	get_lexed(char **temp, t_env *env, t_token_type type);
int	token_init(t_env *env);
int	check_temp(char **temp, t_env *env);
int	handle_quote(char *line, int *i, char **temp, t_env *env);
int	handle_pipe(char **temp, t_env *env);
int	handle_redir(char *line, int *i, char **temp, t_env *env);
int	handle_white_space(int *i, char *line, char **temp,
		t_env *env);
int	init_parser(t_env *env);

#endif
