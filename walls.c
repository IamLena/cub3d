/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:13:44 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/31 16:20:10 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

t_wall_inter	manage_fence(double angle, t_game *game)
{
	double			plpos[2];
	char			**map;
	double			dist_to_wall;
	t_wall_inter	intersect;

	plpos[0] = game->player_pos.x;
	plpos[1] = game->player_pos.y;
	map = (char **)game->map;
	dist_to_wall = 0;
	while (plpos[0] >= 0 && plpos[1] >= 0 && plpos[0] < \
	game->mapwidth && plpos[1] < game->mapheight)
	{
		intersect = get_side(angle, plpos, game);
		dist_to_wall += intersect.dist;
		if (map[intersect.i][intersect.j] == '1')
		{
			intersect.height = game->result.height / (dist_to_wall * \
			cos(to_radians(angle - game->view_angle)));
			return (intersect);
		}
		plpos[0] = intersect.x;
		plpos[1] = intersect.y;
	}
	return (intersect);
}

void			get_wall_intersections(t_game *game)
{
	int				cnt;
	double			anglestep;
	double			angle;
	t_wall_inter	inter;

	cnt = 0;
	anglestep = (double)FOV / (double)game->result.width;
	angle = game->view_angle - FOV / 2;
	if (!game->walls)
		game->walls = malloc(game->result.width * sizeof(t_wall_inter));
	if (game->walls)
	{
		while (cnt < game->result.width)
		{
			inter = manage_fence(angle, game);
			game->walls[cnt] = inter;
			cnt++;
			angle += anglestep;
		}
	}
	else
		seterrorexit(game, MEMERROR, "malloc error\n");
}

void			draw_fc(t_game *game)
{
	int		xy[2];
	int		wh[2];

	xy[0] = 0;
	xy[1] = 0;
	wh[0] = game->result.width;
	wh[1] = game->result.height / 2;
	draw_rect(xy, wh, game->c, game);
	xy[1] = game->result.height / 2;
	draw_rect(xy, wh, game->f, game);
}

void			draw_walls(t_game *game)
{
	int				cnt;
	t_wall_inter	inter;
	int				pixel;
	int				k;

	get_wall_intersections(game);
	draw_fc(game);
	cnt = -1;
	while (++cnt < game->result.width)
	{
		inter = game->walls[cnt];
		pixel = -1;
		while (++pixel < inter.tex->height)
		{
			k = -1;
			while (++k < (inter.height / inter.tex->height))
			{
				my_mlx_pixel_put(game, cnt, (int)(game->result.height / 2 - \
				inter.height / 2 + pixel * (inter.height / inter.tex->height) \
				+ k), *(int*)(inter.tex->addr + (4 * inter.tex->width * \
				pixel) + (4 * (int)(inter.tex_w * inter.tex->width))));
			}
		}
	}
}
