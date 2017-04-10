# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qho <qho@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/08 13:42:02 by qho               #+#    #+#              #
#    Updated: 2017/03/09 14:23:53 by qho              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror

NAME =		my_printf

LIB =		ft_printf.a


INCLUDE =	include/

SRC = 		ft_printf.c	ft_itoa_base.c ft_changecase.c

OBJ =		$(SRC:.c=.o)

.PHONY: clean fclean re norm

all: $(NAME)

$(NAME): $(LIB)
	@$(CC) $(CFLAGS) -o $(NAME) main.c $(LIB) -I $(INCLUDE)
	@echo "\033[32mmy_printf made\033[0m"

$(LIB):		$(OBJ)
	@ar rc $(LIB) $(OBJ)
	@ranlib	$(LIB)
	@echo "\033[32mft_printf.a made\033[0m"

$(OBJ):		$(SRC)
	@$(CC) -c $(CFLAGS) $(SRC) -I $(INCLUDE)
	@echo "\033[32mObject files made\033[0m"

norm:
	@norminette $(SRC) main.c $(INCLUDE)

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[31mCleaning object files\033[0m"

fclean: clean
	@/bin/rm -f $(LIB)
	@echo "\033[31mCleaning ft_printf.a\033[0m"

re: fclean all
