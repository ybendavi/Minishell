NAME = minishell
CC = clang
RM = rm -rf
SRCSDIR = srcs
OBJSDIR = objs
SRCS = main.c libfunc.c libfunc_2.c miniparser.c parser_assets.c execution.c freer.c\
check_parsing_errors.c ft_init.c ft_return.c handle_else.c\
lexer.c parser_init.c token_list_init.c\
handle_quote.c utils_2.c is_pipe.c parser.c utils.c
OBJS = ${SRCS:%.c=${OBJSDIR}/%.o}
$(NAME): ${OBJS}
	$(CC) $(OBJS) -lreadline -o ${NAME}
${OBJS}: ${OBJSDIR}/%.o: ${SRCSDIR}/%.c
	mkdir -p ${OBJSDIR}
	$(CC) -Wall -Wextra -Werror -I./includes -g -c $< -o $@

all: ${NAME}

clean: 
	${RM} ${OBJS}
	${RM} ${OBJSDIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean all fclean re
