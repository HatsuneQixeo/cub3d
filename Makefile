NAME		:=	cub3d

CC			:=	gcc
CXXFLAGS	:=	-Wall -Werror -Wextra
# CXXFLAGS	+=	-g
# CXXFLAGS	+=	-O3
# CXXFLAGS	+=	-Wno-unused-variable -Wno-unused-parameter -Wno-unused-function
# CXXFLAGS	+=	-D IMAGE_OUT_OF_BOUND_CHECK=1
# CXXFLAGS	+=	-D DRAW_WARNING=0
# CXXFLAGS	+=	-D BENCHMARK=1
# CXXFLAGS	+=	-D COLLISION=0
# CXXFLAGS	+=	-D SHOW_RAY=1
# CXXFLAGS	+=	-D DEBUG_KEY=1
# CXXFLAGS	+=	-D DEBUG_BUTTON=1
ifdef SAN
CXXFLAGS	+=	-fsanitize=address -g -D SAN=1
endif
MLXFLAGS	:=	-framework OpenGL -framework AppKit

MLX			:=	mlx/libmlx.a
MLX_MAKE	:=	make -C mlx

SRC_DIR		:=	srcs
SRCS		:=	$(shell find ${SRC_DIR} -name "*.c")

HEADER		:=	$(shell find ${SRC_DIR} -name "*.h")
HEADER		+=	libft/include/libft.h
CFLAGS		:=	$(addprefix -I, $(dir ${HEADER})) -Imlx

OBJ_DIR		:=	objs
OBJS 		:=	$(patsubst ${SRC_DIR}%.c, ${OBJ_DIR}%.o, ${SRCS})

LIBFT		:=	libft/libft.a
LIBFT_MAKE	:=	make -C libft

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
	${MLX_MAKE} 2> /dev/null
	@printf "${LIGHT_CYAN}${CC} ${CXXFLAGS} ${LIBFT} \$${OBJS} ${MLX} ${MLXFLAGS} -o $@${RESET}\n"
	@${CC} ${CXXFLAGS} ${LIBFT} $^ ${MLX} ${MLXFLAGS} -o $@

clean:
	${LIBFT_MAKE} clean
	${MLX_MAKE} clean
	@printf "${RED}${RM} ${OBJ_DIR}${RESET}\n"
	@${RM} -r ${OBJ_DIR}

fclean: clean
	${LIBFT_MAKE} fclean
	@printf "${RED}${RM} ${NAME}${RESET}\n"
	@${RM} ${NAME}

re:	fclean all

thisre:
	${RM} -r ${NAME} ${OBJ_DIR}
	make all

norm:
	@norminette ${SRCS} ${HEADER}

check:
	touch srcs/main.c
	make all
