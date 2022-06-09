/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:46:40 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/06 19:30:54 by ccottin          ###   ########.fr       */
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
	ENV,
	STR,
	QUOTE
}		t_token_type;

typedef struct s_token {
	char			*token;
	uint32_t		size;
	t_token_type	type;
}	t_token;

typedef struct s_env {
	t_token	*tab;
	t_token	*lexed;
	t_token	*parsed;
	char	*error;
	uint32_t	nb_token;
	uint32_t	nb_parsed;
}			t_env;

typedef struct command_table_list
{
	char						**cmd;
	int							in;
	int							out;
	struct command_table_list	*next;
}					t_cmds;

char	**ft_cpy(char **temp, char *s1);
int	get_lexed(char **temp, t_env *data, t_token_type type);
int	token_init(t_env *data);
int	check_temp(char **temp, t_env *data);
int	handle_env(char **temp, t_env *data);
int	handle_pipe(char **temp, t_env *data);
int	handle_redir(char *line, int *i, char **temp, t_env *data);
int	handle_quote(char *line, int *i, char **temp, t_env *data);
int	handle_white_space(int *i, char *line, char **temp,
		t_env *data);
int	init_parser(t_env *data, char **env);
int	ft_cmp(char *s1, char *s2);
int	check_parsing_errors(t_env *data);
void	free_lexed(t_env *data);

/*********UTILS*************/

char	*ft_env_strnstr(const char *big, const char *little, size_t len);
void	*ft_calloc(size_t nmem);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);

#endif
