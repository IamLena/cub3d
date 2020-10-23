/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:13:57 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/23 18:41:57 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_game(t_game *game)
{
	mlx_clear_window(game->mlx_con, game->window);
	mlx_destroy_window(game->mlx_con, game->window);
	exit(SUCCESS);
	return (SUCCESS);
}

int		move_player(int moveangle, t_game *game)
{
	double	x;
	double	y;
	char	**map;

	map = (char **)game->map;
	x = game->player_pos.x + MOVESPEED * \
	sin(to_radians(game->view_angle + moveangle));
	y = game->player_pos.y - MOVESPEED * \
	cos(to_radians(game->view_angle + moveangle));
	if ((int)floor(y) > 0 && (int)floor(y) < \
	game->mapheight && (int)floor(x) > 0 && (int)floor(x) < game->mapwidth)
		if (map[(int)floor(y)][(int)floor(x)] != '1')
		{
			game->player_pos.x = x;
			game->player_pos.y = y;
		}
}

int		press_key(int keycode, t_game *game)
{
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
	return (0);
}

int ft_strcmp(char *str1, char *str2)
{
	if (str1 && str2)
	{
		while (*str1 && *str2)
		{
			if (*str1 != *str2)
				break ;
			str1++;
			str2++;
		}
		if (*str1 == '\0' && *str2 == '\0')
			return (0);
	}
	return 1;
}


void	ft_game_to_image(t_game *data, int fd)
{
	unsigned char	splt_colour[4];
	char			*color;
	int				x;
	int				y;

	y = 0;
	y = data->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < data->width)
		{
			color = data->imgadr + (x * 4 + y * data->llen);
			splt_colour[0] = (unsigned char)(color[0]);
			splt_colour[1] = (unsigned char)(color[1]);
			splt_colour[2] = (unsigned char)(color[2]);
			splt_colour[3] = (unsigned char)(color[3]);
			write(fd, splt_colour, 4);
			x++;
		}
		y--;
	}
}

void ft_bzero(void *addr, size_t bytes)
{
	char *data = (char *)addr;
	int i = 0;
	while (i < bytes)
	{
		*data = 0;
		data++;
		i++;
	}
}

void	ft_info_header(t_game *data, int fd)
{
	unsigned char	bmih[40];
	int				width;
	int				height;

	ft_bzero(&bmih, 40);
	width = data->width;
	height = data->height;
	bmih[0] = (unsigned char)(40);
	bmih[4] = (unsigned char)(width);
	bmih[5] = (unsigned char)(width >> 8);
	bmih[6] = (unsigned char)(width >> 16);
	bmih[7] = (unsigned char)(width >> 24);
	bmih[8] = (unsigned char)(height);
	bmih[9] = (unsigned char)(height >> 8);
	bmih[10] = (unsigned char)(height >> 16);
	bmih[11] = (unsigned char)(height >> 24);
	bmih[12] = (unsigned char)(1);
	bmih[14] = (unsigned char)(32);
	write(fd, bmih, 40);
}

void	ft_file_header(t_game *data, int fd)
{
	unsigned char	bmfh[14];
	int				filesize;

	filesize = (data->width * data->height * 4) + 14 + 40;
	ft_bzero(&bmfh, 14);
	bmfh[0] = 'B';
	bmfh[1] = 'M';
	bmfh[2] = (unsigned char)(filesize);
	bmfh[3] = (unsigned char)(filesize >> 8);
	bmfh[4] = (unsigned char)(filesize >> 16);
	bmfh[4] = (unsigned char)(filesize >> 24);
	bmfh[10] = (unsigned char)(54);
	write(fd, bmfh, 14);
}

void	save_img(t_game *game)
{
	int	fd;

	if ((fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		errorexit(4, "open bmp", 0);
	// ft_check_screen_s(game);
	// ft_create_image(game);
	ft_file_header(game, fd);
	ft_info_header(game, fd);
	ft_game_to_image(game, fd);
	close(fd);
	exit_game(game);
}

int		main(int argc, char **argv)
{
	t_game	game;

	if (argc == 3)
	{
		//--save
		if (ft_strcmp(argv[1], "--save") == 0)
		{
			init_game(argv[2], &game);
			draw_map(&game);
			save_img(&game);
		}
		return (SUCCESS);
	}
	if (argc == 2)
	{
		init_game(argv[1], &game);
		draw_map(&game);
		put_img(&game);
		mlx_hook(game.window, 2, 1L << 0, press_key, &game);
		mlx_hook(game.window, 17, 0L, exit_game, &game);
		mlx_loop(game.mlx_con);
		return (SUCCESS);
	}
	return (ARGSERROR);
}
