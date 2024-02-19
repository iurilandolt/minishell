# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcastelo <rcastelo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 15:32:17 by rlandolt          #+#    #+#              #
#    Updated: 2024/02/19 17:07:50 by rcastelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./sources

SRC = $(SRC_PATH)/main.c \
	$(SRC_PATH)/quote_split/clean_quotes.c \
	$(SRC_PATH)/quote_split/quote_split.c \
	$(SRC_PATH)/check_analyzer/check_analyzer.c \
	$(SRC_PATH)/ambient_variable_expansion/ambient_variable_expansion.c \
	$(SRC_PATH)/string_expander/string_expander.c \
	$(SRC_PATH)/string_contracter/string_contracter.c \
	$(SRC_PATH)/string_utils/string_utils.c \
	$(SRC_PATH)/string_utils/split.c \
	$(SRC_PATH)/token_type/classify_token.c \
	$(SRC_PATH)/token_type/tok_array.c \
	$(SRC_PATH)/token_type/tok_list.c \
	$(SRC_PATH)/cmd_blocks/cmd_blocks.c \
	$(SRC_PATH)/cmd_blocks/cmd_blocks_utils.c \


SANITIZER = -g -fsanitize=address

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

debug: CFLAGS += ${SANITIZER}
debug: re

re: fclean all

.PHONY: all, clean, fclean, re
