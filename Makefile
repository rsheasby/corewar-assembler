# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryan <ryan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/18 18:59:33 by jdamhuis          #+#    #+#              #
#    Updated: 2017/09/30 17:10:11 by ryan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	----------------------------------------------------------------------------
#								echo variables
#	----------------------------------------------------------------------------

#		format   /033[0;31m

RESET	=\033[0m
BLINK	=\033[5m
GREEN	=\033[5;32m
C_ASM	=\033[1;31;43mASM$(RESET)
C_COM	=\033[32mcompiled$(RESET)
C_CLE	=\033[36mcleaned$(RESET)
C_FCLE	=\033[34mfcleaned$(RESET)
C_ARR	=$(GREEN)-->$(RESET)

#	----------------------------------------------------------------------------
#								project variables
#	----------------------------------------------------------------------------

SRCS	=	src/*.c ../op/op.c
HEADERS	=	include/asm.h
IFLAGS	=	-Iinclude/ -I../
LIBFT	=	-L../libft/ -lft
NAME	=	asm
CC		=	clang
CFLAGS	=	-Wall -Werror -Wextra $(IFLAGS) $(LIBFT) -o $(NAME)
OBJS	=	$(SRCS:.c=.o)

#	----------------------------------------------------------------------------
#									rules
#	----------------------------------------------------------------------------

all: $(NAME)

$(NAME):
	@if [ ! -f ../libft/libft.a ]; then \
		make -C ../libft all $(NO_DIR); \
		fi
	@$(CC) $(SRCS) $(CFLAGS) 
	@echo "\t\t\t$(C_ARR) $(C_ASM) has been $(C_COM)"

debug: fclean
	@$(CC) $(SRCS) $(CFLAGS) -g
	@echo "\t\t\t$(C_ARR) $(C_ASM) has been $(C_COM) with debugging symbols."

clean:
	@rm -f $(OBJS)
	@echo "\t\t\t$(C_ARR) $(C_ASM) has been $(C_CLE)"

fclean: clean
	@rm -f $(NAME)
	@echo "\t\t\t$(C_ARR) $(C_ASM) has been $(C_FCLE)"

re: fclean all

norm:
	@echo "Norminetting asm:"
	@norminette $(HEADERS)
	@echo "\t\t$(C_ARR) Headers Done."
	@norminette $(SRCS)
	@echo "\t\t$(C_ARR) Sources Done."


.PHONY: clean fclean re norm all
