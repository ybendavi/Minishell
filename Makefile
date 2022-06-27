NAME = minishell
CC = clang
RM = rm -rf
SRCSDIR = srcs
OBJSDIR = objs
SRCS =  parsing/libfunc.c parsing/libfunc_2.c exec/print_exec_error.c exec/miniparser.c exec/parser_assets.c exec/execution.c exec/freer.c\
parsing/check_parsing_errors.c parsing/ft_init.c parsing/ft_return.c parsing/handle_else.c parsing/ft_itoa.c ft_env.c ft_exit.c\
parsing/lexer.c parsing/parser_init.c parsing/token_list_init.c signal_init.c signal_errors.c ft_export.c parsing/main.c\
parsing/handle_quote.c parsing/utils_2.c parsing/is_env.c parsing/parser.c parsing/utils.c exec/path_handler.c exec/builtin.c ft_cd.c\
ft_echo.c ft_unset.c
OBJS = ${SRCS:%.c=${OBJSDIR}/%.o}
$(NAME): ${OBJS}
	$(CC) $(OBJS) -lreadline -o ${NAME}
${OBJS}: ${OBJSDIR}/%.o: ${SRCSDIR}/%.c
	mkdir -p ${OBJSDIR}/parsing
	mkdir -p ${OBJSDIR}/exec
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
