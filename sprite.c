#include "sprite.h"

static t_sprite *new_sprite(int i, int j)
{
	t_sprite *new;
	new = malloc(sizeof(t_sprite));
	if (new)
	{
		new->y = i;
		new->x = j;
		new->height = -1;
		new->dist = -1;
		new->next = 0;
		new->cansee = 0;
	}
	return (new);
}

void add_sprite(t_sprite **sprites_list, int i, int j)
{
	if (sprites_list)
	{
		t_sprite *new = new_sprite(i, j);
		if (*sprites_list)
		{
			t_sprite *cur = *sprites_list;
			while (cur->next)
			{
				cur = cur->next;
			}
			cur->next = new;
		}
		else
		{
			*sprites_list = new;
		}
	}
}

static void append_to_sorted(t_sprite **sorted, t_sprite *sprite)
{
	t_sprite *cur;
	t_sprite *prev;

	if (!sprite->cansee)
		return;
	if (*sorted == 0)
	{
		sprite->next = 0;
		*sorted = sprite;
	}
	else
	{
		cur = *sorted;
		prev = NULL;
		while (cur->dist >= sprite->dist)
		{
			prev = cur;
			cur = cur->next;
			// cutting the tail!
		}
		sprite->next =  cur;
		if (prev == NULL)
			*sorted = sprite;
		else
			prev->next = sprite;
	}

}

static t_sprite *sort_by_dist(t_sprite *list)
{
	//error
	t_sprite *sorted = 0;
	while (list)
	{
		append_to_sorted(&sorted, list);
		list = list->next;
	}
	return sorted;
}

static t_sprite	*setdists_sort(t_sprite *sprite, t_dot player)
{
	double x2;
	double y2;
	double dist;
	t_sprite *cur;

	cur = sprite;
	while (cur)
	{
		x2 = (player.x - cur->x - 0.5) * (player.x - cur->x - 0.5);
		y2 = (player.y - cur->y - 0.5) * (player.y - cur->y - 0.5);
		dist = sqrt(y2 + x2);
		cur->dist = dist;
		cur = cur->next;
	}
	return sort_by_dist(sprite);
}

void	saw_sprite(t_sprite *list, int i, int j)
{
	while (list && list->y != i && list->x != j)
	{
		list = list->next;
	}
	if (list)
		list->cansee = 1;
}

static double get_angle(double dx, double dy, double c)
{
	if (dx >= 0 && dy >= 0)
		return (360 - to_degrees(asin(dx / c)));
	if (dx >= 0 && dy <= 0)
		return (360 - (180 - to_degrees(asin(dx / c))));
	if (dx <= 0 && dy >= 0)
		return (360 - (360 + to_degrees(asin(dx / c))));
	return (360 - (180 -  to_degrees(asin(dx / c))));
	//error here
	// не 360, asin возвращает -90 ; + 90
	// return (360 - to_degrees(asin(dx / c)));
	// спрайт двигается если смотреть под углом и идти
}

void draw_sprite(t_game *game)
{
	t_sprite *sorted_list = setdists_sort(game->sprites, game->player_pos);
	while(sorted_list)
	{
		game->view_angle = fmod(game->view_angle, 360);
		// DOES NOT WORK PROPERLY
		double anglestep = (double)FOV / (double)game->width;
		double angle = get_angle(game->player_pos.x - sorted_list->x - 0.5, game->player_pos.y - sorted_list->y - 0.5, sorted_list->dist);
		double xline = game->width / 2  + (angle - game->view_angle) / anglestep; //center
		// double x2 = (game->player_pos.x - sorted_list->x - 1) * (game->player_pos.x - sorted_list->x - 1);
		// double y2 = (game->player_pos.y - sorted_list->y - 1) * (game->player_pos.y - sorted_list->y - 1);
		// double distto0 = sqrt(y2 + x2);
		// double angle = get_angle(game->player_pos.x - sorted_list->x - 1, distto0);
		// double xline0 = game->width / 2  + (angle - game->view_angle) / anglestep;

		// x2 = (game->player_pos.x - sorted_list->x) * (game->player_pos.x - sorted_list->x);
		// y2 = (game->player_pos.y - sorted_list->y) * (game->player_pos.y - sorted_list->y);
		// distto0 = sqrt(y2 + x2);
		// angle = get_angle(game->player_pos.x - sorted_list->x, distto0);
		// double xline1 = game->width / 2  + (angle - game->view_angle) / anglestep;

		// double width= abs(xline0 - xline1);
		double height = WIN_H / sorted_list->dist;
		double width = height;
		double xline0 = xline - width / 2;

		double height_scale = height / game->s_tex.height;
		double width_scale = width / game->s_tex.width;
		int pixelx = 0;
		while (pixelx < game->s_tex.width)
		{
			int pixely = 0;
			while (pixely < game->s_tex.height)
			{
				int kx = 0;
				int color = *(int*)(game->s_tex.addr + (4 * game->s_tex.width * pixely) + (4 * pixelx));
				if (color != -16777216)
				{
					while (kx < width_scale)
					{
						int ky = 0;
						while (ky < height_scale)
						{
							if ((int)(xline0 + pixelx * width_scale + kx) >= 0 && \
							(int)(xline0 + pixelx * width_scale + kx) <= game->width && \
							(int)(game->height / 2 - height / 2 + pixely * height_scale + ky) >= 0 && \
							(int)(game->height / 2 - height / 2 + pixely * height_scale + ky) <= game->width)
								my_mlx_pixel_put(game, (int)(xline0 + pixelx * width_scale + kx), (int)(game->height / 2 - height / 2 + pixely * height_scale + ky), color);
							ky++;
						}
						kx++;
					}
				}
				pixely++;
			}
			pixelx++;
		}
		sorted_list->cansee = 0;
		// draw_rect(x, game->height / 2 - height / 2, 1, height , 0, game);
		sorted_list = sorted_list->next;
	}
}
