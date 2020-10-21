NAME = cub3D
CC = gcc
# FLAGS = -Wall -Wextra -Werror -I.
FLAGS = -g -I.
MLX = libmlx.a
# MLX = libmlx.dylib
MLXDIR = ./mlx/
LIBS = -L mlx -lmlx -L /usr/include/../lib -lXext -lX11 -lm -lbsd
# LIBS = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
SRC = main.c init.c tools.c draw_tools.c draw.c maprow.c gnl_loop.c map.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(MLX):
	$(MAKE) -C $(MLXDIR)
	# mv $(MLXDIR)/$(MLX) .

%.o : %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -rf *.o

fclean: clean
	rm -rf cub3D $(MLX)

re: fclean all
