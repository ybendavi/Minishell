/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:46:40 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/02 21:07:23 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef enum e_token_type {
	REDIR_ADD,
	REDIR_LIM,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	QUOTE,
	S_QUOTE,
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

typedef struct command_table_list
{
	char						**cmds;
	char						*cmd;
	char						*file_in;
	char						*file_out;
	int							in;
	int							out;
	int							*pfd;
	struct command_table_list	*next;
	struct command_table_list	*prev;
}					t_cmds;

typedef struct s_env {
	t_token	*tab;
	t_token	*lexed;
	t_cmds	*c_tbls;
	char	**env;
	int	fd_size;
	int	pfd_size;
	uint32_t	size;
}			t_env;

char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	parsing(t_env *envs, char *av);
void	free_cmds_table(t_cmds *tbls);
#endif
