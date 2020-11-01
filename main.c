/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 21:01:32 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/31 16:19:19 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "errors.h"
#include "tools.h"
#include "initgame.h"
#include "draw.h"
#include "sprite.h"
#include "save.h"

#define NAME "cub3d"
#define BMPNAME "image.bmp"
#define ESC 65307
#define RIGHTTURN 65363
#define LEFTTURN 65361
#define FORWARD 119
#define BACKWARD 115
#define LEFTSIDE 97
#define RIGHTSIDE 100
#define TURNSPEED 5
#define MOVESPEED 0.1

void		move_player(int moveangle, t_game *game)
{
	double	x;
	double	y;
	char	**map;

	map = (char **)game->map;
	x = game->player_pos.x + (0.1 + MOVESPEED) * \
	sin(to_radians(game->view_angle + moveangle));
	if ((int)floor(x) >= 0 && (int)floor(x) < game->mapwidth)
		if (map[(int)floor(game->player_pos.y)][(int)floor(x)] != '1')
		{
			game->player_pos.x = game->player_pos.x + MOVESPEED * \
			sin(to_radians(game->view_angle + moveangle));
		}
	y = game->player_pos.y - (0.1 + MOVESPEED) * \
	cos(to_radians(game->view_angle + moveangle));
	if ((int)floor(y) >= 0 && (int)floor(y) < game->mapheight)
		if (map[(int)floor(y)][(int)floor(game->player_pos.x)] != '1')
		{
			game->player_pos.y = game->player_pos.y - MOVESPEED * \
			cos(to_radians(game->view_angle + moveangle));
		}
}

int			press_key(int keycode, t_game *game)
{
	if (keycode == ESC)
		exitgame(game);
	else if (keycode == RIGHTTURN)
		game->view_angle = fmod(game->view_angle + TURNSPEED, 360);
	else if (keycode == LEFTTURN)
		game->view_angle = fmod(game->view_angle - TURNSPEED, 360);
	else if (keycode == FORWARD)
		move_player(0, game);
	else if (keycode == BACKWARD)
		move_player(180, game);
	else if (keycode == LEFTSIDE)
		move_player(-90, game);
	else if (keycode == RIGHTSIDE)
		move_player(90, game);
	draw_walls(game);
	draw_sprites(game);
	put_img(game);
	return (0);
}

static void	screenshot(t_game *game, char *cubfile, char *bmpfile)
{
	init_game(game, cubfile);
	draw_walls(game);
	draw_sprites(game);
	save_img(game, bmpfile);
	exitgame(game);
}

static void	play(t_game *game, char *filename)
{
	init_game(game, filename);
	if (!(game->window = mlx_new_window(game->mlx_con, \
	game->result.width, game->result.height, NAME)))
		seterrorexit(game, MLXERROR, "window creation failed\n");
	draw_walls(game);
	draw_sprites(game);
	put_img(game);
	mlx_hook(game->window, 2, 1L << 0, press_key, game);
	mlx_hook(game->window, 17, 1L << 17, exitgame, game);
	mlx_loop(game->mlx_con);
}

int			main(int argc, char **argv)
{
	t_game game;

	if (argc == 3)
		if (ft_streq(argv[2], "--save"))
			screenshot(&game, argv[1], BMPNAME);
	if (argc == 2)
		play(&game, argv[1]);
	ft_write("Error\n./cub3D filename.cub [--save]\n");
	return (ARGERROR);
}
