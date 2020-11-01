NAME = cub3D
CC = gcc
FLAGS = -Wall -Wextra -Werror -g -I .

MLX = libmlx.a
MLXDIR = ./mlx_linux/
LIBS = -L . -lmlx -L /usr/include/../lib -lXext -lX11 -lm -lbsd

SRC = main.c initgame.c gnl_loop.c parsemap.c tools1.c tools2.c tools3.c tools4.c tools5.c maprow.c sprite.c walls.c save.c drawsprite.c sides.c parsefile.c
OBJ = $(SRC:.c=.o)
HEADERS = draw.h errors.h initgame.h maprow.h save.h sprite.h structures.h tools.h

all : $(NAME)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(MLX):
	$(MAKE) -C $(MLXDIR)
	cp $(MLXDIR)$(MLX) ./$(MLX)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	$(MAKE) clean -C $(MLXDIR)
	rm -rf $(OBJ)

fclean: clean
	rm -rf cub3D $(MLX) *.bmp

re: fclean all
