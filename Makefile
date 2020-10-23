NAME = cub3D
CC = gcc
# FLAGS = -Wall -Wextra -Werror -I.
FLAGS = -g -I.

#for wsl
MLX = libmlx.a
MLXDIR = ./mlx_linux/
LIBS = -L mlx_linux -lmlx -L /usr/include/../lib -lXext -lX11 -lm -lbsd

SRC = main.c init.c tools.c tools2.c tools3.c draw_tools.c draw.c maprow.c gnl_loop.c map.c sprite.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(MLX):
	$(MAKE) -C $(MLXDIR)

%.o : %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	$(MAKE) clean -C $(MLXDIR)
	rm -rf $(OBJ)

fclean: clean
	# $(MAKE) fclean -C $(MLXDIR) not working
	rm -rf cub3D $(MLX)

re: fclean all
