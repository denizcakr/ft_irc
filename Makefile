# Derleyici ve bayraklar
NAME = ircserv
CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98 -Wshadow -O3

# Dizinler
SRC_DIR = source
CMD_DIR = $(SRC_DIR)/commands
INC_DIR = include

# Kaynak dosyaları
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(CMD_DIR)/*.cpp)

# Varsayılan hedef
all: $(NAME)

# Programı oluştur
$(NAME): $(SRCS)
	$(CC) $(FLAGS) -I$(INC_DIR) $^ -o $@

# Temizlik
clean:
	rm -f $(NAME)

run: clean all
	@if [ -f $(NAME) ]; then \
		echo "Running $(NAME)..."; \
		./$(NAME) 8080 123; \
	else \
		echo "Executable $(NAME) not found!"; \
	fi

# Yeniden derleme
re: clean all

.PHONY: all clean re run
