# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 15:32:17 by rlandolt          #+#    #+#              #
#    Updated: 2024/02/23 15:31:16 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./sources

SRC = $(SRC_PATH)/main.c \
	$(SRC_PATH)/Parsing/quote_split/clean_quotes.c \
	$(SRC_PATH)/Parsing/quote_split/quote_split.c \
	$(SRC_PATH)/Parsing/check_analyzer/check_analyzer.c \
	$(SRC_PATH)/Parsing/ambient_variable_expansion/ambient_variable_expansion.c \
	$(SRC_PATH)/Parsing/string_expander/string_expander.c \
	$(SRC_PATH)/Parsing/string_contracter/string_contracter.c \
	$(SRC_PATH)/Parsing/string_utils/split.c \
	$(SRC_PATH)/Parsing/token_type/classify_token.c \
	$(SRC_PATH)/Parsing/token_type/tok_array.c \
	$(SRC_PATH)/Parsing/token_type/tok_list.c \
	$(SRC_PATH)/Parsing/tokenize/tokenize.c \
	$(SRC_PATH)/Parsing/tokens_check/tokens_check.c \
	$(SRC_PATH)/Setup/create_pipes/create_pipes.c \
	$(SRC_PATH)/Setup/obtain_commands/obtain_commands.c \
	$(SRC_PATH)/Setup/obtain_commands/check_bin_path.c \
	$(SRC_PATH)/Setup/obtain_documents/obtain_read_documents.c \
	$(SRC_PATH)/Setup/obtain_documents/obtain_write_documents.c \
	$(SRC_PATH)/Setup/obtain_operators/obtain_operators.c \
	$(SRC_PATH)/Utils/string_utils/string_utils.c \
	$(SRC_PATH)/Utils/get_next_line/get_next_line.c \
	$(SRC_PATH)/Utils/get_next_line/get_next_line_utils.c \
	$(SRC_PATH)/Utils/prints/print_session.c \

SANITIZER = -g -fsanitize=address

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ =$(addprefix objects/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

objects/%.o: */%.c| objects
	cc $(CFLAGS) -c $< -o $@

objects/%.o: */*/*/%.c | objects
	cc $(CFLAGS) -c $< -o $@

objects:
	mkdir objects

print-%:
	@echo $* = $($*)

clean:
		rm -rf $(OBJ) objects

fclean: clean
		rm -f $(NAME)

debug: CFLAGS += ${SANITIZER}
debug: re

re: fclean all

.PHONY: all, clean, fclean, re
