# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qho <qho@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/08 13:42:02 by qho               #+#    #+#              #
#    Updated: 2017/04/19 23:42:57 by qho              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
EXE		=	my_printf

# Flags and compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

# Source and header files, and directory
INC		=	./inc/
FILES	=	ft_getdata ft_make_num ft_make_ptr ft_make_str ft_make_wstr 	\
			ft_make_wstr_2		\
			ft_modnum ft_modnum_2 ft_parse ft_parse_2 ft_printf ft_put_pf	\
			ft_strings_1 ft_strings_2 ft_width_pres ft_wstrings_1
SRC		=	$(addprefix src/, $(addsuffix .c, $(FILES)))

# Object directory and files
OBJ	=	$(addsuffix .o, $(FILES))

.PHONY: clean fclean re norm

all: $(OBJ) $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib	$(NAME)
	@echo "\033[32mft_printf.a made\033[0m"

$(OBJ):	$(SRC)
	@$(CC) -c $(CFLAGS) $(SRC) -I$(INC)
	@echo "\033[32mObject files made\033[0m"

test: $(NAME)
	# @$(CC) -Wformat -I$(INC) $(NAME) main.c -o $(EXE)
	# clang -fsanitize=address -I$(INC) $(NAME) main.c
	clang -I$(INC) $(NAME) main.c

norm:
	@norminette $(SRC) $(INC)

clean:
	@/bin/rm -rf $(OBJ)
	@echo "\033[31mCleaning object files\033[0m"

fclean: clean
	@/bin/rm -f $(NAME) $(EXE)
	@echo "\033[31mCleaning ft_printf.a\033[0m"

re: fclean all
