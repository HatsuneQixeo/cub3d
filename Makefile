NAME		:=	cub3d

CC			:=	gcc
CXXFLAGS	:=	-Wall -Werror -Wextra -g
CXXFLAGS	+=	-Wno-unused-variable -Wno-unused-parameter -Wno-unused-function
# CXXFLAGS	+=	-D DRAW_WARNING=0
# CXXFLAGS	+=	-D DEBUG_KEY=1
# CXXFLAGS	+=	-D DEBUG_BUTTON=1
MLXFLAGS	:=	-lmlx -framework OpenGL -framework AppKit -L /usr/local/lib

ifdef SAN
CXXFLAGS	+=	-fsanitize=address -g -D SAN=1
endif
MLX			:=	mlx/libmlx.a
MLX_MAKE	:=	make -C mlx 2> /dev/null

SRC_DIR		:=	srcs
SRCS		:=	$(shell find ${SRC_DIR} -name "*.c")

HEADER		:=	$(shell find ${SRC_DIR} -name "*.h") libft/include/libft.h
CFLAGS		:=	$(addprefix -I, $(dir ${HEADER})) -I mlx

OBJ_DIR		:=	objs
OBJS 		:=	$(patsubst ${SRC_DIR}%.c, ${OBJ_DIR}%.o, ${SRCS})

LIBFT		:=	libft/libft.a
LIBFT_MAKE	:=	make -C libft

RM			:=	rm -rf

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
	@printf "${CYAN}${CC} ${CXXFLAGS} \$${CFLAGS} -c $< -o $@${RESET}\n"
	@${CC} ${CXXFLAGS} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${LIBFT_MAKE}
	${MLX_MAKE}
	@printf "${LIGHT_CYAN}${CC} ${CXXFLAGS} $^ -o $@${RESET}\n"
	@${CC} ${CXXFLAGS} ${LIBFT} $^ ${MLX} ${MLXFLAGS} -o $@

clean:
	${LIBFT_MAKE} clean
	${MLX_MAKE} clean
	@printf "${RED}${RM} ${OBJ_DIR}${RESET}\n"
	@${RM} ${OBJ_DIR}

fclean: clean
	${LIBFT_MAKE} fclean
	@printf "${RED}${RM} ${NAME}${RESET}\n"
	@${RM} ${NAME}

re:	fclean all

run: ${NAME}
	./$<

log: ${NAME}
	./$< > log.log

thisre:
	${RM} ${NAME} ${OBJ_DIR}
	make all

norm:
	@norminette ${SRC_DIR} ${HEADER}

normltr:
	@norminette -R CheckForbiddenSourceHeader ${SRC_DIR} ${HEADER} | grep -v INVALID_HEADER | grep -v WRONG_SCOPE_COMMENT # | grep -v LINE_TOO_LONG
