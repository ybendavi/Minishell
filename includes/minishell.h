/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:46:40 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/27 23:59:04 by ccottin          ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

typedef enum e_token_type {
	REDIR_ADD,
	REDIR_LIM,
	REDIR_IN,
	REDIR_OUT,
	PIPE,
	WHITE_SPACE,
	ENV,
	STR
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
	char						*path;
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
	t_token	*parsed;
	int	status_code;
	char	*error;
	char	*cupath;
	char	**temp;
	uint32_t	nb_token;
	uint32_t	nb_parsed;
  t_cmds	*c_tbls;
	char	**env;
//	int	fd_size;
//	int	pfd_size;
}			t_env;

/****exec*****/
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	set_cmds(t_cmds *c_tbls, t_token *token);
int	cmds_len(t_cmds *c_tbls, t_token *token);
int	set_fd(t_cmds *c_tbls, t_token *token);
t_token_type	choose_tok(char *str);
int	new_fd(char *filename, t_token_type type);
int	parsing(t_env *envs);
int	set_paths(t_env *env);
int	exec_errors(int status_code, const char *cmd, t_env *envs);
int	is_builtin(t_cmds *cmds);
int	builtins(t_cmds *cmds, char **env, t_env *envs);
void	paths_free(char **paths);
char	**set_env(char **env);
int	execution(t_env *envs);
void	free_cmds_table(t_cmds *tbls);
void	free_pfds(t_cmds *cmds);
void	freeer(t_env *envs);
/****parser*****/
char	**ft_cpy(char **temp, char *s1);
char	*ft_concat(char *s1, char *s2);
int	get_lexed(char **temp, t_env *data, t_token_type type);
int	token_init(t_env *data);
int	check_temp(char **temp, t_env *data);
int	handle_pipe(char **temp, t_env *data);
int	handle_env(char **temp, t_env *data, unsigned int *i, char *line);
int	handle_redir(char *line, unsigned int *i, char **temp, t_env *data);
int	handle_quote(char *line, unsigned int *i, char **temp, t_env *data);
int	handle_white_space(unsigned int *i, char *line, char **temp,
		t_env *data);
int	init_parser(t_env *data, char **env);
int	is_env(unsigned int *i, t_env *data, char **env);
int	is_str(unsigned int *i, t_env *data);
int	ft_cmp(char *s1, char *s2);
int	ft_init(t_env *data, char **env);
int	check_parsing_errors(t_env *data);
int	lexer(char *line, t_env *data);
int	is_pipe(unsigned int i, t_env *data);
int	get_parsed(t_env *data, t_token token);
int	ft_return(int ret, t_env *data);
int	is_whitespace(unsigned int *i, t_env *data);
int	is_redir(unsigned int i, t_env *data);
void	add_temp(char *line, char **temp, unsigned int i);

/*********SIG***********/

char	*sig_error(int sig);
int	signal_init(void);

/********BUILT-IN*********/

int	ft_export(char **strs, t_env *data);
int	cd_main(char **av, t_env *envs);
int	pwd_main(t_env *envs);
int	ft_env(t_env *data, char **strs);
int	ft_unset(char **strs, t_env *data);
int	ft_echo(char **strs);
void	ft_exit(t_env *data, char **strs);

/*********UTILS*************/

char	*ft_env_strnstr(const char *big, const char *little, size_t len);
char	*ft_cpy2(char *s1);
void	*ft_calloc(size_t nmem);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
int	ft_isdigit(int c);
int	ft_strcmp(char *s1, char *s2);
int	is_str_env(char c);
int	is_char_env(char c);
int	ft_mcpy(char *s1, char **s2);
void	free_all(t_env *data);
void	free_parsed(t_env *data);
void	free_env(t_env *data);
void	free_lexed(t_env *data);
void	set_null(t_env *data);

#endif
