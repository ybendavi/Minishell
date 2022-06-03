NAME = minishell
CC = gcc
RM = rm -rf
SRCSDIR = srcs
OBJSDIR = objs
SRCS = main.c libfunc.c libfunc_2.c miniparser.c parser_assets.c execution.c freer.c 
OBJS = ${SRCS:%.c=${OBJSDIR}/%.o}
$(NAME): ${OBJS}
	$(CC) $(OBJS) -Wall -Wextra -Werror -o ${NAME}
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
