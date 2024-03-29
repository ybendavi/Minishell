NAME = minishell
CC = clang
RM = rm -rf
SRCSDIR = srcs
OBJSDIR = objs
SRCS = main.c utils/libfunc.c utils/libfunc_two.c exec/print_exec_error.c exec/miniparser.c exec/parser_assets.c exec/execution.c exec/freer.c exec/redir_parse.c exec/new_table.c exec/child_processes.c exec/exec_assets.c exec/path_handler_p2.c exec/exec_no_pipe.c exec/cmds_parse.c exec/sig.c exec/lim_exec.c exec/fds_closer.c exec/parent_delim.c builtin/ft_exit2.c exec/file_parser.c\
parsing/check_parsing_errors.c parsing/ft_init.c parsing/ft_return.c parsing/handle_else.c parsing/ft_itoa.c builtin/ft_env.c builtin/ft_exit.c builtin/ft_export_two.c\
parsing/lexer.c parsing/parser_init.c parsing/token_list_init.c signal_init.c signal_errors.c builtin/ft_export.c\
parsing/handle_quote.c utils/utils_2.c parsing/parser.c utils/utils.c exec/path_handler.c exec/builtin.c builtin/ft_cd.c\
builtin/ft_echo.c builtin/ft_unset.c parsing/count_lexer_token.c parsing/count_lexer_token_2.c parsing/count_parser_token.c builtin/ft_pwd.c\
parsing/handle_env.c parsing/ft_return_2.c builtin/ft_unset_2.c parsing/handle_env_2.c parsing/lexer2.c
OBJS = ${SRCS:%.c=${OBJSDIR}/%.o}
$(NAME): ${OBJS}
	$(CC) $(OBJS) -Wall -Wextra -Werror -lreadline -o ${NAME}
${OBJS}: ${OBJSDIR}/%.o: ${SRCSDIR}/%.c
	mkdir -p ${OBJSDIR}/parsing
	mkdir -p ${OBJSDIR}/builtin
	mkdir -p ${OBJSDIR}/exec
	mkdir -p ${OBJSDIR}/utils
	cd ..
	$(CC) -Wall -Wextra -Werror -I./includes -g -c $< -o $@

all: ${NAME}

clean: 
	${RM} ${OBJS}
	${RM} ${OBJSDIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean all fclean re
