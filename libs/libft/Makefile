# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaela <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/18 14:03:12 by lbaela            #+#    #+#              #
#    Updated: 2022/01/18 18:34:31 by lbaela           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFILES =	ft_bzero.c			ft_memset.c			\
			ft_memcpy.c			ft_memccpy.c		\
			ft_memmove.c		ft_memchr.c			\
			ft_memcmp.c								\
			ft_strncmp.c		ft_strlen.c			ft_strlcpy.c		\
			ft_strlcat.c		ft_strchr.c			ft_strrchr.c		\
			ft_strnstr.c		ft_atoi.c			ft_atoi_base.c		\
			ft_isalpha.c		ft_isdigit.c		ft_isalnum.c		\
			ft_isascii.c		ft_isprint.c							\
			ft_toupper.c		ft_tolower.c							\
			ft_calloc.c			ft_strdup.c								\
			ft_substr.c			ft_strjoin.c		ft_strtrim.c		\
			ft_split.c			ft_split_free.c							\
			ft_itoa.c			ft_strmapi.c							\
			ft_putchar_fd.c		ft_putstr_fd.c		ft_putendl_fd.c		\
			ft_putnbr_fd.c												\
			ft_lstnew.c			ft_lstadd_front.c	ft_lstsize.c		\
			ft_lstlast.c		ft_lstadd_back.c	ft_lstdelone.c		\
			ft_lstclear.c		ft_lstiter.c		ft_lstmap.c			\
			get_next_line.c

C_PRINTF =	ft_printf/ft_printf.c										\
			ft_printf/print_control_string.c							\
			ft_printf/arg_parser/print_arg.c							\
			ft_printf/arg_parser/get_arg.c								\
			ft_printf/arg_parser/modify_arg.c							\
			ft_printf/str_converter/trim_and_align_str.c				\
			ft_printf/str_converter/trim_and_align_digit.c				\
			ft_printf/str_converter/ft_itoa_d.c							\
			ft_printf/str_converter/ft_itoa_u.c							\
			ft_printf/str_converter/ft_itoa_x.c							\
			ft_printf/str_converter/ft_itoa_f.c							\
			ft_printf/str_converter/ft_itoa_f_utils.c					\
			ft_printf/str_converter/convert_arg_s.c						\
			ft_printf/str_converter/convert_arg_c_prc.c					\
			ft_printf/str_converter/convert_arg_d_u_i_f.c				\
			ft_printf/str_converter/convert_arg_n.c						\
			ft_printf/str_converter/convert_arg_x_p.c

OBJS		= $(CFILES:.c=.o) $(C_PRINTF:.c=.o)

D_FILES		= $(CFILES:.c=.d) $(C_PRINTF:.c=.d)

INCLUDES	= -I.

CC			= gcc

FLAGS		= -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $?

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

clean :
	@rm -f $(OBJS) $(D_FILES)
	@echo "\033[1;38;5;221m*  Libft objects removed\033[0m"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[1;38;5;221m*  Libft.a removed\033[0m"

re : fclean all

.PHONY : all clean fclean re
