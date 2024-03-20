# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 15:32:17 by rlandolt          #+#    #+#              #
#    Updated: 2024/03/20 16:35:47 by rlandolt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./sources

SRC = $(SRC_PATH)/main.c \
	$(SRC_PATH)/Parsing/quote_split/clean_quotes.c \
	$(SRC_PATH)/Parsing/quote_split/quote_split.c \
	$(SRC_PATH)/Parsing/check_analyzer/check_analyzer.c \
	$(SRC_PATH)/Parsing/string_expander/string_expander.c \
	$(SRC_PATH)/Parsing/string_contracter/string_contracter.c \
	$(SRC_PATH)/Parsing/string_utils/split.c \
	$(SRC_PATH)/Parsing/token_type/classify_token.c \
	$(SRC_PATH)/Parsing/token_type/tok_array.c \
	$(SRC_PATH)/Parsing/tokenize/tokenize.c \
	$(SRC_PATH)/Parsing/tokens_check/tokens_check.c \
	$(SRC_PATH)/Setup/create_pipes/create_pipes.c \
	$(SRC_PATH)/Setup/obtain_commands/obtain_commands.c \
	$(SRC_PATH)/Setup/obtain_documents/obtain_read_documents.c \
	$(SRC_PATH)/Setup/obtain_documents/obtain_write_documents.c \
	$(SRC_PATH)/Setup/obtain_operators/obtain_operators.c \
	$(SRC_PATH)/Setup/list_process_ids/list_process_ids.c \
	$(SRC_PATH)/Utils/string_utils/string_utils.c \
	$(SRC_PATH)/Utils/string_utils/string_utils2.c \
	$(SRC_PATH)/Utils/string_utils/str_fd.c \
	$(SRC_PATH)/Utils/string_utils/itoa.c \
	$(SRC_PATH)/Utils/get_next_line/get_next_line.c \
	$(SRC_PATH)/Utils/get_next_line/get_next_line_utils.c \
	$(SRC_PATH)/Utils/free_all/free_session.c \
	$(SRC_PATH)/Utils/prints/print_session.c \
	$(SRC_PATH)/Utils/string_utils/str_sort.c \
	$(SRC_PATH)/Tasks/Builtins/builtin_exec/builtin_writeto.c \
	$(SRC_PATH)/Task/ambient_variable_expansion/ambient_variable_expansion.c \
	$(SRC_PATH)/Tasks/organize_after_expansion/organize_after_expansion.c \
	$(SRC_PATH)/Tasks/check_commands/check_bin_path.c \
	$(SRC_PATH)/Tasks/check_commands/checkbin_utils.c \
	$(SRC_PATH)/Tasks/perform_tasks/perform_tasks.c \
	$(SRC_PATH)/Tasks/close_opened_fds/close_opened_fds.c \
	$(SRC_PATH)/Tasks/open_taskfiles/open_taskfiles.c \
	$(SRC_PATH)/Tasks/perform_redirects/perform_redirects.c \
	$(SRC_PATH)/Tasks/Builtins/check_builtin/check_builtin.c \
	$(SRC_PATH)/Tasks/Builtins/chgdir/chgdir.c \
	$(SRC_PATH)/Tasks/Builtins/chgdir/setup_cd.c \
	$(SRC_PATH)/Tasks/Builtins/env/menvp.c \
	$(SRC_PATH)/Tasks/Builtins/env/menvp_input.c \
	$(SRC_PATH)/Tasks/Builtins/env/menvp_utils.c \
	$(SRC_PATH)/Tasks/Builtins/env/parse_export.c \
	$(SRC_PATH)/Tasks/Builtins/env/export_operations.c \
	$(SRC_PATH)/Tasks/Builtins/echo/echo.c \
	$(SRC_PATH)/Tasks/Builtins/exit/exit.c \
	$(SRC_PATH)/Signals/received_signals/received_signals.c\
	$(SRC_PATH)/Signals/main_signals/main_signals.c\
	$(SRC_PATH)/Signals/task_signals/task_signals.c\
	$(SRC_PATH)/Signals/ignore_signals/ignore_signals.c\


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

objects/%.o: */*/*/*/%.c | objects
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
