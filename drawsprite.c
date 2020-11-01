/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 13:56:26 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 02:22:56 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

void		put_pixel_if(int pixelx, int pixely, t_sprite *sprite, t_game *game)
{
	int	kx;
	int	ky;
	int	x;
	int	y;
	int	color;

	if ((color = *(int*)(game->s_tex.addr + (4 * game->s_tex.width * pixely) \
	+ (4 * pixelx))) == -16777216)
		return ;
	kx = -1;
	while (++kx < (sprite->width / game->s_tex.width))
	{
		ky = -1;
		while (++ky < (sprite->height / game->s_tex.height))
		{
			x = pixelx * (sprite->width / game->s_tex.width) + kx;
			y = game->result.height / 2 - sprite->height / 2 + \
			pixely * (sprite->height / game->s_tex.height) + ky;
			if (sprite->cnt + x >= 0 && sprite->cnt + x <= game->result.width \
			&& y >= 0 && y <= game->result.height && \
			game->walls[sprite->cnt + x].height < sprite->height)
				my_mlx_pixel_put(game, sprite->cnt + x, y, color);
		}
	}
}

void		draw_one_sprite(t_sprite *sprite, t_game *game)
{
	int pixelx;
	int pixely;

	pixelx = -1;
	while (++pixelx < game->s_tex.width)
	{
		pixely = -1;
		while (++pixely < game->s_tex.height)
		{
			put_pixel_if(pixelx, pixely, sprite, game);
		}
	}
	sprite->dist = -1;
}

static void	append_to_sorted(t_sprite **sorted, t_sprite *sprite, t_game *game)
{
	t_sprite	*cur;
	t_sprite	*prev;
	t_sprite	*copy;

	if ((copy = copy_sprite(sprite)))
	{
		cur = *sorted;
		prev = NULL;
		while (cur && cur->dist >= sprite->dist)
		{
			prev = cur;
			cur = cur->next;
		}
		if (prev == NULL)
		{
			*sorted = copy;
			(*sorted)->next = cur;
			return ;
		}
		prev->next = copy;
		prev->next->next = cur;
		return ;
	}
	seterror(game, MEMERROR, "malloc error in copy\n");
}

void		sort_sprites(t_sprite **list, t_game *game)
{
	t_sprite	*cur;
	t_sprite	*sorted;

	cur = *list;
	sorted = 0;
	while (cur)
	{
		append_to_sorted(&sorted, cur, game);
		if (game->rc)
			break ;
		cur = cur->next;
	}
	free_list(*list);
	*list = sorted;
}

void		draw_sprites(t_game *game)
{
	t_sprite	*sorted_list;

	game->view_angle = fmod(game->view_angle, 360);
	sprite_info(game);
	sort_sprites(&game->sprites, game);
	if (game->rc)
		exitgame(game);
	sorted_list = game->sprites;
	while (sorted_list)
	{
		if (sorted_list->dist <= 0.1)
			break ;
		draw_one_sprite(sorted_list, game);
		sorted_list = sorted_list->next;
	}
}
