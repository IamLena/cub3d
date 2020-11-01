/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 01:59:54 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:41:19 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

int			add_sprite(t_sprite **sprites_list, int i, int j, t_texture *tex)
{
	t_sprite	*new;
	t_sprite	*cur;

	if (!sprites_list || !(new = malloc(sizeof(t_sprite))))
		return (1);
	new->y = i + 0.5;
	new->x = j + 0.5;
	new->height = 0;
	new->width = 0;
	new->dist = -1;
	new->next = 0;
	new->cnt = -1;
	new->tex = tex;
	if (*sprites_list)
	{
		cur = *sprites_list;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	else
		*sprites_list = new;
	return (0);
}

double		get_angle(t_game *game, t_sprite *list)
{
	double	dx;
	double	dy;
	double	c;
	double	angle;

	dx = game->player_pos.x - list->x;
	dy = game->player_pos.y - list->y;
	c = list->dist;
	if (dx >= 0 && dy >= 0)
		angle = 360 - to_degrees(asin(dx / c));
	else if (dx >= 0 && dy <= 0)
		angle = 180 + to_degrees(asin(dx / c));
	else if (dx <= 0 && dy >= 0)
		angle = -to_degrees(asin(dx / c));
	else
		angle = 180 + to_degrees(asin(dx / c));
	angle -= game->view_angle;
	if (angle > 180)
		angle -= 360;
	if (angle < -180)
		angle += 360;
	return (angle);
}

void		sprite_info(t_game *game)
{
	t_sprite	*list;
	double		x2;
	double		y2;
	double		anglestep;
	double		deltaangle;

	list = game->sprites;
	while (list)
	{
		x2 = (game->player_pos.x - list->x) * (game->player_pos.x - list->x);
		y2 = (game->player_pos.y - list->y) * (game->player_pos.y - list->y);
		list->dist = sqrt(y2 + x2);
		anglestep = (double)FOV / (double)game->result.width;
		deltaangle = get_angle(game, list);
		list->height = game->result.height / list->dist / \
		cos(to_radians(deltaangle));
		list->width = game->result.width / list->dist;
		if (list->width / 2 > game->result.width ||
		(abs(deltaangle) - list->width / 2 * anglestep) > FOV / 2)
			list->dist = -1;
		else
			list->cnt = game->result.width / 2 + \
			deltaangle / anglestep - list->width / 2;
		list = list->next;
	}
}

t_sprite	*copy_sprite(t_sprite *origin)
{
	t_sprite	*new;

	if (!origin)
		return (0);
	new = malloc(sizeof(t_sprite));
	if (new)
	{
		new->y = origin->y;
		new->x = origin->x;
		new->height = origin->height;
		new->width = origin->width;
		new->dist = origin->dist;
		new->cnt = origin->cnt;
		new->tex = origin->tex;
		new->next = origin->next;
	}
	return (new);
}

void		free_list(t_sprite *list)
{
	t_sprite	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
