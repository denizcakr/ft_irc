NAME = ircserv
BOT_NAME = ircbot
CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98 -Wshadow -O3

SRC_DIR = source
BOT_DIR = $(SRC_DIR)/BOT
CMD_DIR = $(SRC_DIR)/commands
INC_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(CMD_DIR)/*.cpp)
BOT_SRCS = $(wildcard $(BOT_DIR)/*.cpp)

all: $(NAME) $(BOT_NAME)

$(NAME): $(SRCS)
	$(CC) $(FLAGS) -I$(INC_DIR) $^ -o $@

$(BOT_NAME) : $(BOT_SRCS)
	$(CC) $(FLAGS) -I$(INC_DIR) $^ -o $@

clean:
	rm -f $(NAME) $(BOT_NAME)

fclean: clean
	@rm -f $(NAME) $(BOT_NAME)
	@echo "$(NAME) and $(BOT_NAME) : $(RED)$(NAME)$(BOT_NAME) was deleted$(RESET)"

run: clean all
	@if [ -f $(NAME) ]; then \
		echo "Running $(NAME)..."; \
		./$(NAME) 8080 123; \
	else \
		echo "Executable $(NAME) not found!"; \
	fi

re: clean all

.PHONY: all clean fclean re bonus
