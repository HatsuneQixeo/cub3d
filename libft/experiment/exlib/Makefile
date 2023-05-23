NAME 		:=	exlib.a

CC			:=	gcc
CXXFLAGS	:=	-Wall -Werror -Wextra

SRC_DIR		:=	srcs
SRCS		:=	$(shell find ${SRC_DIR} -name "*.c")

OBJ_DIR		:=	objs
OBJS 		:=	$(patsubst ${SRC_DIR}%.c, ${OBJ_DIR}%.o, ${SRCS})

LIBFT_PATH	:=	../..
LIBFT		:=	${LIBFT_PATH}/libft.a

INCLUDE		:=	include
HEADER		:=	$(wildcard ${INCLUDE}/*.h) ${LIBFT_PATH}/include/
CFLAGS		:=	$(addprefix -I, $(dir ${HEADER}))

GREY		:=	\033[30m
RED			:=	\033[31m
CYAN		:=	\033[36m
LIGHT_CYAN	:=	\033[1;36m
RESET		:=	\033[0m

all: ${NAME}

${OBJ_DIR}:
	@printf "${GREY}mkdir $@${RESET}\n"
	@mkdir $@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${HEADER} | ${OBJ_DIR}
	@mkdir -p ${@D}
	@printf "${CYAN}${CC} ${CXXFLAGS} ${CFLAGS} -c $< -o $@${RESET}\n"
	@${CC} ${CXXFLAGS} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	@printf "${LIGHT_CYAN}ar rcs $@ $^${RESET}\n"
	@ar rcs $@ $^

clean:
	@printf "${RED}${RM} -r ${OBJ_DIR}${RESET}\n"
	@${RM} -r ${OBJ_DIR}

fclean: clean
	@printf "${RED}${RM} ${NAME}${RESET}\n"
	@${RM} ${NAME}

re:	fclean all

run: ${NAME}
	./$<

log: ${NAME}
	./$< > log.log
