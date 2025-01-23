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
NAME_BONUS = philo_bonus

CC = cc
LIB = ar rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined,leak -g3

HEADER = include/pipex.h
HEADER_BONUS = include/pipex_bonus.h

SRC_DIR = src
SRC_DIR_BONUS = src_bonus
SRCS = $(SRC_DIR)/philo.c
SRCS_BONUS = $(SRC_DIR_BONUS)/pipex_bonus.c $(SRC_DIR_BONUS)/utils_bonus.c

OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

RED         = \033[91;1m
GREEN       = \033[92;1m
CLEAR_COLOR = \033[0m

all: $(NAME)

bonus: $(NAME_BONUS)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled! ;)$(CLEAR_COLOR)\n"

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
	@echo "$(GREEN)$(NAME_BONUS) compiled! ;)$(CLEAR_COLOR)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c $(HEADER_BONUS)
	@mkdir -p $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@


clean:
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@echo "$(RED)Object files removed!$(CLEAR_COLOR)\n"

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)All files removed!$(CLEAR_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re bonus