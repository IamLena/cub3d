#include "cub3d.h"

int exit_game(t_game *game)
{
	mlx_clear_window(game->mlx_con, game->window);
	mlx_destroy_window(game->mlx_con, game->window);
	exit(0);
	return 0;
}

int move_player(int moveangle, t_game *game)
{
	double x;
	double y;
	char **map;

	// printf("%f %f\n", game->player_pos.x, game->player_pos.y);

	map = (char **)game->map;
	x = game->player_pos.x + MOVESPEED * sin(to_radians(game->view_angle + moveangle));
	y = game->player_pos.y - MOVESPEED * cos(to_radians(game->view_angle + moveangle));
	if ((int)floor(y) > 0 && (int)floor(y) < game->mapheight && (int)floor(x) > 0 && (int)floor(x) < game->mapwidth)
		if (map[(int)floor(y)][(int)floor(x)] != '1')
		{
			game->player_pos.x = x;
			game->player_pos.y = y;
		}
}

int press_key(int keycode, t_game *game)
{
	printf("%d\n", keycode);
	if (keycode == ESC)
		exit_game(game);
	else if (keycode == RIGHTTURN)
		game->view_angle += TURNSPEED;
	else if (keycode == LEFTTURN)
		game->view_angle -= TURNSPEED;
	else if (keycode == FORWARD)
		move_player(0, game);
	else if (keycode == BACKWARD)
		move_player(180, game);
	else if (keycode == LEFTSIDE)
		move_player(-90, game);
	else if (keycode == RIGHTSIDE)
		move_player(90, game);
	draw_map(game);
	// obj->flag = 1;
	return 0;
}

// int render(t_game *game)
// {
// 	// print_matrix(game->map);
// 	// draw_map(&game);
// 	// put_img(&game);
// }

int main(int argc, char **argv)
{
	t_game game;
	if (argc == 3)
	{
		//--save
		return (SUCCESS);
	}
	if (argc == 2)
	{
		init_game(argv[1], &game);
		draw_map(&game);
		// mlx_loop_hook(game.mlx_con, render, &game);
		mlx_hook(game.window, 2, 1L<<0, press_key, &game);
		mlx_hook(game.window, 17, 0L, exit_game, &game);
		mlx_loop(game.mlx_con);
		return (SUCCESS);
	}
	return (ARGSERROR);
}
