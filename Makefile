# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvan-wij <fvan-wij@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 18:08:39 by fvan-wij          #+#    #+#              #
#    Updated: 2022/11/11 14:22:54 by fvan-wij         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	get_next_line.a

HEADER		:=	get_next_line.h

SRC			:=	get_next_line.c \
					ft_strchr.c \
					ft_strjoin.c \
					ft_strlen.c

OBJ 		:= $(SRC:.c=.o)

CC			:= gcc

CFLAGS		:= -Wall -Werror -Wextra

RMV			:= rm -f

# Regular Colors
Black		= "\033[0;30m"		# Black
Red			= "\033[0;31m"		# Red
Green		= "\033[0;32m"		# Green
Yellow		= "\033[0;33m"		# Yellow
Blue		= "\033[0;34m"		# Blue
Purple		= "\033[0;35m"		# Purple
Cyan		= "\033[0;36m"		# Cyan
White		= "\033[0;37m"		# White

# Reset
Text_Off	= "\033[0m"			# Text Reset

#Text styles
Bold		= "\033[1m"

$(NAME): 	$(OBJ)
			@ar -rcs $(NAME) $(OBJ)
			@echo $(Green) $(Bold)Completed ✅ $(Text_Off)

all: 		$(NAME)

%.o: 		%.c
			@echo $(Blue)Building... $^ $(Text_Off)
			@$(CC) $(CFLAGS) -c -o $@ $^

clean: 		
			@echo $(Yellow)Cleaned all object files! $(Text_Off)
			@$(RMV) $(OBJ)

fclean: 	clean
			@echo $(Yellow)Cleaned libft.a! $(Text_Off)
			@$(RMV) $(NAME)

re: 		fclean $(NAME)

.PHONY:		all clean fclean re

