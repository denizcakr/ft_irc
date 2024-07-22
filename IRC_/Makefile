# Derleyici ve bayraklar
NAME = ircserv
CC = c++
FLAGS = -Wall -Werror -Wextra -std=c++98 -Wshadow -O3

# Dizinler
SRC_DIR = source
INC_DIR = include
OBJ_DIR = objects

# Kaynak dosyaları
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Hedef program adı (istediğiniz ismi buraya yazabilirsiniz)

# Varsayılan hedef
all: $(NAME)

# Programı oluştur
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

# Obje dosyalarını oluştur
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $@

# Temizlik
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

run: re
	@./ircserv 8080 123

# Yeniden derleme
re: fclean all

.PHONY: all clean fclean re