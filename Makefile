NAME = cub3D
CC = cc
SRC_DIR = src
OBJ_DIR = obj
CFLAGS = -Wall -Wextra -Werror -I includes

SRCS_LIST = main.c \
			map_file/init.c map_file/check.c map_file/utils.c \
			map/clear.c map/check.c map/utils.c \
			game/check.c game/clear.c \
			images/clear.c \
			player/check.c player/init.c \
			utils/ft_strlen.c utils/ft_strdup.c utils/ft_strncmp.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRCS_LIST))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
