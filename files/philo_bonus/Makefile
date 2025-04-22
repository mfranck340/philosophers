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

NAME = philo_bonus

CC = cc
LIB = ar rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g3

HEADER = include/philo_bonus.h

SRC_DIR = src
SRCS = $(SRC_DIR)/philo_bonus.c \
		$(SRC_DIR)/checks.c \
		$(SRC_DIR)/init.c 

OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RED         = \033[91;1m
GREEN       = \033[92;1m
CLEAR_COLOR = \033[0m

BANNER = "$(GREEN)"\
"          ______  _     _ _       ______                         "\
" _  _    (_____ \| |   (_) |     (____  \                        "\
"( \( \    _____) ) | _  _| | ___  ____)  ) ___  ____  _   _  ___ "\
" ) )) )  |  ____/| || \| | |/ _ \|  __  ( / _ \|  _ \| | | |/___)"\
"(_/(_/   | |     | | | | | | |_| | |__)  ) |_| | | | | |_| |___ |"\
"         |_|     |_| |_|_|_|\___/|______/ \___/|_| |_|\____(___/ "\
"$(CLEAR_COLOR)"

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
