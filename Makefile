# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 17:40:17 by ujyzene           #+#    #+#              #
#    Updated: 2019/08/09 02:45:14 by ujyzene          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

INCL_DIR = includes
LIBFT_DIR = libft
SRCS_DIR = sources
OBJS_DIR = tmp
LIB = $(LIBFT_DIR)/libft.a

FILES = ft_printf.c \
		pf_chars_handlers.c \
		pf_float_handlers.c \
		pf_helpers.c \
		pf_num_handlers.c \
		pf_parce_format.c \
		pf_parse.c \
		pf_pfs.c \
		pf_vprintf.c \



SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))

LIBFT_INCL = -I $(LIBFT_DIR)/includes
LIBFT_LINK = -L $(LIBFT_DIR) -lft

.PHONY : all clean fclean re

all : $(NAME)

$(LIB) :
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(FLAGS) $(LIBFT_INCL) -I $(INCL_DIR) -o $@ -c $<

$(NAME) : $(LIB) $(OBJS)
	ar rcs $(NAME) $(OBJS) $(LIBFT_DIR)/*.o
	ranlib $(NAME)

$(OBJS_DIR) :
	mkdir $(OBJS_DIR)

clean :
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re : fclean all
