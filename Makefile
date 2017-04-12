# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qho <qho@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/08 13:42:02 by qho               #+#    #+#              #
#    Updated: 2017/04/11 22:51:18 by qho              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
EXE		=	my_printf

# Flags and compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

# Source and header files, and directory
INC		=	./inc/
SRCDIR 	=	./src/
SRC		=	$(shell ls src | grep -E ".+\.c")

# Object directory and files
OBJDIR	=	./obj/
OBJ	=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

.PHONY: clean fclean re norm

all: $(OBJDIR) $(NAME)

# Making directory for object files
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@$(CC) $(CFLAGS) -I$(INC) -o $@ -c $<
	@echo "\033[32mObject files made\033[0m"

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib	$(NAME)
	@echo "\033[32mft_printf.a made\033[0m"

test: $(NAME)
	@$(CC) $(CFLAGS) -I$(INC) $(NAME) main.c -o $(EXE)

norm:
	@norminette $(SRC) $(INC)

clean:
	@/bin/rm -rf $(OBJDIR)
	@echo "\033[31mCleaning object files\033[0m"

fclean: clean
	@/bin/rm -f $(LIB)
	@echo "\033[31mCleaning ft_printf.a\033[0m"

re: fclean all
