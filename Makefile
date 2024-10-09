NAME = cub3D
CC = cc
SRCS = $(shell find src -type f -name "*.c")
OBJS = $(patsubst src/%, obj/%, $(SRCS:.c=.o))
CFLAGS = -Wall -Wextra -Werror -I includes -I minilibx-linux
MLXFLAGS = -lXext -lX11 -lm
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

all: $(MLX) $(NAME)

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git; \
	fi
	cd $(MLX_DIR) && $(MAKE)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX) $(MLXFLAGS)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
