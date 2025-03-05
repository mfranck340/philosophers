# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 17:42:15 by ffierro-          #+#    #+#              #
#    Updated: 2024/12/26 17:42:16 by ffierro-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
LIB = ar rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g3

HEADER = include/philo.h

SRC_DIR = src
SRCS = $(SRC_DIR)/philo.c $(SRC_DIR)/utils.c $(SRC_DIR)/init.c \
		$(SRC_DIR)/simulation.c $(SRC_DIR)/checks.c

OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RED         = \033[91;1m
GREEN       = \033[92;1m
CLEAR_COLOR = \033[0m

BANNER = "$(GREEN)         __   _ __                           _ __       __"\
"   ___  / /  (_) /__    _______  __ _  ___  (_) /__ ___/ /"\
"  / _ \/ _ \/ / / _ \  / __/ _ \/  ' \/ _ \/ / / -_) _  /"\
" / .__/_//_/_/_/\___/  \__/\___/_/_/_/ .__/_/_/\__/\_,_/"\
"/_/                                 /_/$(CLEAR_COLOR)\n"

all: $(NAME)

$(NAME): $(OBJS)
	@echo ""
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "%b\n" $(BANNER)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@
	@echo -n "\rCompiling $<"

clean:
	$(RM) $(OBJ_DIR)
	@echo "$(RED)Object files removed!$(CLEAR_COLOR)\n"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)All files removed!$(CLEAR_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
