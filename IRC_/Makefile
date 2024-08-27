NAME = ircserv
CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98 -Wshadow -O3

SRC_DIR = source
CMD_DIR = $(SRC_DIR)/commands
INC_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(CMD_DIR)/*.cpp)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(FLAGS) -I$(INC_DIR) $^ -o $@

clean:
	rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

run: clean all
	@if [ -f $(NAME) ]; then \
		echo "Running $(NAME)..."; \
		./$(NAME) 8080 123; \
	else \
		echo "Executable $(NAME) not found!"; \
	fi

re: clean all

.PHONY: all clean re run
