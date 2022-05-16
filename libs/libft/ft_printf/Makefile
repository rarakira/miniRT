NAME		= libftprintf.a

LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

CFILES	=	ft_printf.c								\
			print_control_string.c					\
			arg_parser/print_arg.c					\
			arg_parser/get_arg.c					\
			arg_parser/modify_arg.c					\
			str_converter/trim_and_align_str.c		\
			str_converter/trim_and_align_digit.c	\
			str_converter/ft_itoa_d.c				\
			str_converter/ft_itoa_u.c				\
			str_converter/ft_itoa_x.c				\
			str_converter/ft_itoa_f.c				\
			str_converter/ft_itoa_f_utils.c			\
			str_converter/convert_arg_s.c			\
			str_converter/convert_arg_c_prc.c		\
			str_converter/convert_arg_d_u_i_f.c		\
			str_converter/convert_arg_n.c			\
			str_converter/convert_arg_x_p.c

OBJS		= $(CFILES:.c=.o)

CC			= gcc

FLAGS		= -Wall -Werror -Wextra -Iincludes

all : get_libft $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@cp $(LIBFT_DIR)/libft.a ./$(NAME)
	ar rcs $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

bonus : get_libft $(NAME)

get_libft :
	@$(MAKE) -C $(LIBFT_DIR)

clean :
	@$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean : clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re : fclean all

norme :
	@norminette $(CFILES) includes/*.h $(LIBFT_DIR)/*.c

.PHONY : all clean fclean re bonus norme
