/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:46:40 by ybendavi          #+#    #+#             */
/*   Updated: 2022/06/01 19:20:22 by ccottin          ###   ########.fr       */
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

typedef struct s_env {
	t_token	*tab;
	t_token	*lexed;
	uint32_t	size;
}			t_env;

typedef struct command_table_list
{
	char						**cmd;
	int							in;
	int							out;
	struct command_table_list	*next;
}					t_cmds;

#endif
