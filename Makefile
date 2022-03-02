include makefile.srcs

NAME			=	miniRT

SRCS_DIR		=	srcs

OBJS_DIR		=	objs

OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

D_FILES			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))

INCLUDES		=	-Iincludes -I./libs/libft -I./libs/minilibx_macos

H_FILES			=	includes/minirt.h								\
					includes/parsing.h								\
					includes/error.h								\
					includes/structure_prototypes.h					\
					libs/minilibx_macos/mlx.h

XLIB			=	mlx

XLIBDIR			=	libs/minilibx_macos

LIB_MLX			=	$(XLIBDIR)/libmlx.a

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

XFLAGS			=	-framework OpenGL -framework AppKit

OPTFLAGS		=	-MMD -MP -g -O2

RM				=	rm -rf

all : $(dir $(LIB_MLX)) $(NAME)

$(NAME) : $(OBJS) $(LIB_MLX)
		$(CC) $(OBJS) -L$(XLIBDIR) -l$(XLIB) $(XFLAGS) -o $(NAME)

bonus : all

.SECONDEXPANSION:
${OBJS} :	$$(patsubst %.o, %.c, $$(subst ${OBJS_DIR}/, ${SRCS_DIR}/, $${@}))
			@mkdir -p ${@D}
			${CC} ${CFLAGS} ${OPTFLAGS} ${INCLUDES} -c $< -o $@

-include ${OBJS:.o=.d}

norm :
			@norminette  srcs/* includes/*

$(dir $(LIB_MLX)) :
			@make -C $@ $(MAKECMDGOALS)

clean :		$(dir $(LIB_FT))
			@$(RM) $(OBJS) $(D_FILES)
			@echo "\033[1;38;5;221m*  MLX objects removed\033[0m"
			@echo "\033[1;38;5;221m*  miniRT objects removed\033[0m"

fclean :	clean
			@$(RM) $(NAME)
			@$(MAKE) clean -C $(XLIBDIR)
			@#rm -rf objs
			@rm -rf *.dSYM 
			@echo "\033[1;38;5;221m*  miniRT program removed\033[0m"

re :		fclean all

.PHONY: all bonus clean fclean $(dir $(LIB_MLX)) re norm
