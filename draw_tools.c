/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:30:43 by nalecto           #+#    #+#             */
/*   Updated: 2020/09/14 09:42:48 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_tools.h"
#include "cub3d.h"

int rgb_to_int(int r, int g, int b)
{
    int color;
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (-1);
    
    color = (0 << 24 | r << 16 | g << 8 | b);
    return (color);
}

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char *dst;
    
    dst = game->imgadr + (y * game->llen + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_square(int x, int y, int width, int color, t_game *game)
{
    int i, j;
    
    i = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			my_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void put_img(t_game *game)
{
	mlx_put_image_to_window(game->mlx_con, game->window, game->img, 0, 0);
}

void draw_rect(int x, int y, int width, int height, int color, t_game *game)
{
    int i, j;
    
    i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			my_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

double to_degrees(double radians)
{
    return radians * (180.0 / M_PI);
}

double to_radians(double degrees)
{
	return degrees / 180.0 * M_PI;
}