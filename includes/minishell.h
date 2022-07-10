/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:46:40 by ybendavi          #+#    #+#             */
/*   Updated: 2022/07/10 15:44:13 by ccottin          ###   ########.fr       */
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
	STR
}		t_token_type;

typedef struct s_token {
	char			*token;
	uint32_t		size;
	t_token_type	type;
}	t_token;

typedef struct fds_list
{
	int	fd;
	struct fds_list	*next;
}			t_fds;

typedef struct command_table_list
{
	char						**cmds;
	char						*cmd;
	char						*path;
	char						*file_in;
	char						*file_out;
	char						**delim;
	int							status;
	int							in;
	int							out;
	int							*lim;
	int							*pfd_in;
	int							*pfd_out;
	pid_t						fork;
	t_fds				*fds;
	struct command_table_list	*next;
	struct command_table_list	*prev;
}					t_cmds;

typedef struct s_env {
	struct sigaction	sig_i;
	struct sigaction	sig_q;
	t_token				*tab;
	t_token				*lexed;
	t_token				*parsed;
	char				*error;
	char				*cupath;
	char				**temp;
	t_cmds				*c_tbls;
	char				**env;
	int					status_code;
	int					nb_sig;
	unsigned int		nb_token;
	unsigned int		nb_parsed;
}			t_env;

/****exec*****/

t_token_type	choose_tok(char *str);
char			**ft_split(char const *s, char c);
char			**set_env(char **env);
char			*ft_strdup(const char *s);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				set_cmds(t_cmds *c_tbls, t_token *token);
int				cmds_len(t_cmds *c_tbls, t_token *token);
int				set_fd(t_cmds *c_tbls, t_token *token);
int				new_fd(char *filename, t_token_type type);
int				parsing(t_env *envs);
int				is_redir_rec(t_token *tokens);
int				redir_parse(t_env *envs, t_token *token);
int				new_table(t_env *envs);
int				set_paths(t_env *env);
int				set_path_error(char **paths);
int				lim_handler(t_cmds *cmd, t_env *envs);
int				child_process(t_cmds *cmd, char **env, t_env *envs, int ret);
int				exec_errors(int status_code, const char *cmd, t_env *envs);
int				errno_two(const char *cmd, t_env *envs);
int				is_builtin(t_cmds *cmds);
int				builtins(t_cmds *cmds, char **env, t_env *envs);
int				exec_no_pipe(t_cmds *cmd, t_env *envs);
int				execution(t_env *envs);
int				close_fds(t_cmds *cmd);
int				child_waiter(t_cmds *cmds, t_env *envs, int status, int status_code);
void			exit_int(t_env *envs, char **buff);
int				parent_process(t_cmds *cmds, int status, t_env *envs);
void			redir_handler(t_cmds *cmd);
void			free_all_env(t_env *env);
void			paths_free(char **paths);
void			free_cmds_table(t_cmds *tbls);
void			free_pfds(t_cmds *cmds);
void			freeer(t_env *envs);
void			free_exec(t_env *envs);

/****parser*****/

char			**ft_cpy(char **temp, char *s1);
char			*ft_concat(char *s1, char *s2);
int				find_var_name(char *line, unsigned int *i, char **var);
int				get_lexed(char **temp, t_env *data, t_token_type type);
int				token_init(t_env *data);
int				check_temp(char **temp, t_env *data);
int				handle_pipe(char **temp, t_env *data);
int				handle_env(char **temp, t_env *data, unsigned int *i,
					char *line);
int				handle_redir(char *line, unsigned int *i, char **temp,
					t_env *data);
int				handle_quote(char *line, unsigned int *i, char **temp,
					t_env *data);
int				handle_white_space(unsigned int *i, char *line,
					char **temp, t_env *data);
int				count_lexer_token(char *line, char **temp,
					t_env *data, unsigned int i);
int				count_env(char **temp, char *line, unsigned int *i, t_env *data);
int				count_quote(char *line, unsigned int *i, char **temp);
int				count_pipe(char **temp);
int				count_parser_token(t_env *data);
int				count_temp(char **temp);
int				init_parser(t_env *data);
int				size_of_env(char *line, unsigned int *i, t_env *data);
int				count_size_temp(char *line, t_env *data);
int				is_env(unsigned int *i, t_env *data, char *str);
int				is_str(unsigned int *i, t_env *data);
int				ft_cmp(char *s1, char *s2);
int				ft_init(t_env *data, char **env);
int				check_parsing_errors(t_env *data);
int				lexer(char *line, t_env *data);
int				is_pipe(unsigned int i, t_env *data);
int				get_parsed(t_env *data, t_token token);
int				ft_return(int ret, t_env *data);
int				is_whitespace(unsigned int *i, t_env *data);
int				is_redir(unsigned int i, t_env *data);
int				ft_getenv(char *var, char **str, char **env);
int				is_status_code(unsigned int *i, char **temp, t_env *ata);
int				digit_var(char **temp, t_env *data, unsigned int *i, char *line);
void			add_temp(char *line, char **temp, unsigned int i);

/*********SIG***********/

char			*sig_error(int sig);
int				signal_init(t_env *data);
int				check_sig(int status, t_env *envs);
int    				sig_back(t_env *envs, int status_code);
void			handler_sig(int sig);
void			handler_child(int sig);
void			kill_int(int sig);

/********BUILT-IN*********/

int				ft_export(char **strs, t_env *data);
int				not_valid(char *str);
int				is_good_str(char *str);
int				print_env_w_export(t_env *data);
int				add_to_var(char **env, char *str, int y);
int				handle_add(t_env *data, char *str, int plus);
int				cd_main(char **av, t_env *envs);
int				pwd_main(t_env *envs);
int				ft_env(t_env *data, char **strs);
int				ft_unset(char **strs, t_env *data);
int				ft_echo(char **strs);
int				ft_exit(t_env *data, char **strs);
int				malloc_error(char **neww);

/*********UTILS*************/

char			*ft_env_strnstr(const char *big, const char *little,
					size_t len);
char			*ft_cpy2(char *s1);
char			*ft_itoa(int n);
char			*ft_strchr(const char *s, int c);
void			*ft_calloc(size_t nmem);
size_t			ft_strlen(const char *str);
int				check_global(void);
int				ft_isdigit(int c);
int				ft_strcmp(char *s1, char *s2);
int				is_str_env(char c);
int				is_char_env(char c);
int				ft_mcpy(char *s1, char **s2);
void			free_all(t_env *data);
void			free_parsed(t_env *data);
void			free_env(t_env *data);
void			free_lexed(t_env *data);
void			set_null(t_env *data);

#endif
