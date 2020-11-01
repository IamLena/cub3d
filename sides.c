/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sides.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:22:44 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/28 15:23:19 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

t_wall_inter	calc_north(double angle, double plpos[2], t_game *game)
{
	t_wall_inter	intersect;

	intersect.dist = 2;
	intersect.tex = NULL;
	if (cos(to_radians(angle)) < 0)
	{
		intersect.dist = (plpos[1] - floor(plpos[1]) - 1) \
		/ cos(to_radians(angle));
		intersect.x = plpos[0] + intersect.dist * sin(to_radians(angle));
		intersect.y = floor(plpos[1]) + 1;
		intersect.i = intersect.y;
		intersect.tex_w = ceil(intersect.x) - intersect.x;
		intersect.tex = &(game->no_tex);
		intersect.j = floor(intersect.x);
	}
	return (intersect);
}

t_wall_inter	calc_south(double angle, double plpos[2], t_game *game)
{
	t_wall_inter	intersect;

	intersect.dist = 2;
	intersect.tex = NULL;
	if (cos(to_radians(angle)) > 0)
	{
		intersect.dist = (plpos[1] - ceil(plpos[1]) + 1) \
		/ cos(to_radians(angle));
		intersect.x = plpos[0] + intersect.dist * sin(to_radians(angle));
		intersect.y = ceil(plpos[1]) - 1;
		intersect.i = intersect.y - 1;
		intersect.tex_w = intersect.x - floor(intersect.x);
		intersect.tex = &(game->so_tex);
		intersect.j = floor(intersect.x);
	}
	return (intersect);
}

t_wall_inter	calc_west(double angle, double plpos[2], \
t_wall_inter intersect, t_game *game)
{
	double	sin_an;

	sin_an = sin(to_radians(angle));
	if (sin_an > 0 && \
	(floor(plpos[0]) + 1 - plpos[0]) / sin_an < intersect.dist)
	{
		intersect.dist = (floor(plpos[0]) + 1 - plpos[0]) / sin_an;
		intersect.x = floor(plpos[0]) + 1;
		intersect.y = plpos[1] - intersect.dist * cos(to_radians(angle));
		intersect.i = floor(intersect.y);
		intersect.j = intersect.x;
		intersect.tex_w = intersect.y - floor(intersect.y);
		intersect.tex = &(game->we_tex);
	}
	return (intersect);
}

t_wall_inter	calc_east(double angle, double plpos[2], \
t_wall_inter intersect, t_game *game)
{
	double	sin_an;

	sin_an = sin(to_radians(angle));
	if (sin_an < 0 && \
	(ceil(plpos[0]) - 1 - plpos[0]) / sin_an < intersect.dist)
	{
		intersect.dist = (ceil(plpos[0]) - 1 - plpos[0]) / sin_an;
		intersect.x = ceil(plpos[0]) - 1;
		intersect.y = plpos[1] - intersect.dist * cos(to_radians(angle));
		intersect.i = floor(intersect.y);
		intersect.j = intersect.x - 1;
		intersect.tex_w = ceil(intersect.y) - intersect.y;
		intersect.tex = &(game->ea_tex);
	}
	return (intersect);
}

t_wall_inter	get_side(double angle, double plpos[2], t_game *game)
{
	t_wall_inter	intersect;

	intersect = calc_north(angle, plpos, game);
	if (!intersect.tex)
		intersect = calc_south(angle, plpos, game);
	intersect = calc_east(angle, plpos, intersect, game);
	intersect = calc_west(angle, plpos, intersect, game);
	intersect.i = (intersect.i < 0) ? 0 : intersect.i;
	intersect.j = (intersect.j < 0) ? 0 : intersect.j;
	if (intersect.i >= game->mapheight)
		intersect.i = game->mapheight - 1;
	if (intersect.j >= game->mapwidth)
		intersect.j = game->mapwidth - 1;
	return (intersect);
}
