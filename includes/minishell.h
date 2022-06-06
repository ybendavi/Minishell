/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:46:40 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/06 16:00:56 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
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
	int							*pfd_in;
	int							*pfd_out;
	pid_t							fork;
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
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int	set_cmds(t_cmds *c_tbls, char **strs);
int	cmds_len(t_cmds *c_tbls, char **strs);
int	set_fd(t_cmds *c_tbls, char **strs);
t_token_type	choose_tok(char *str);
int	new_fd(char *filename, t_token_type type);
int	parsing(t_env *envs, char *av);
int	execution(t_env *envs);
void	free_cmds_table(t_cmds *tbls);
void	free_pfds(t_cmds *cmds);
void	freeer(t_env *envs);
#endif
