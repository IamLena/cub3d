#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <stdio.h>
# include "mlx/mlx.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>
# include "tools.h"
# include "draw_tools.h"
# include "maprow.h"
# include "cubstruct.h"

// # define ESC 53
// # define RIGHTTURN 124
// # define LEFTTURN 123
// # define FORWARD 13
// # define BACKWARD 1
// # define LEFTSIDE 0
// # define RIGHTSIDE 2

# define ESC 65307
# define RIGHTTURN 65363
# define LEFTTURN 65361
# define FORWARD 119
# define BACKWARD 115
# define LEFTSIDE 97
# define RIGHTSIDE 100

# define TURNSPEED 10
# define MOVESPEED 0.1

# define KEY_PRESS 2
# define KEY_RELEASED 3
# define CROSS_CLOSE 17 //not working
# define NOEVENTMASK 0L
# define KEYPRESSMASK 1L<<0
# define KEYRELEASEMASK 1L<<1

# define SUCCESS 0
# define ARGSERROR 1
# define FILEERROR 2
# define MAPERROR 3
# define MLXERROR 4

# define NAME "my cub3d"





void	init_game(char *filename, t_game *game);
int		gnl_in_loop(char *line, t_game *game, char **msg);
int		parsemap(t_game *game, char **msg);

int		draw_map(t_game *game);
// void	draw_pixel(t_game *game, int x, int y, int color);
// int		render(t_game *game);

// int		exit_game(t_game *game);
// int		keypressed(int keycode, t_game *game);
// int		keyreleased(int keycode, t_game *game);

#endif
