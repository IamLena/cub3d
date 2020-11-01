/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 00:11:04 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:29:49 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int		rgb_to_int(int rgb[3])
{
	int	r;
	int	g;
	int	b;
	int	color;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = (0 << 24 | r << 16 | g << 8 | b);
	return (color);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < game->result.width && y >= 0 && y < game->result.height)
	{
		dst = game->result.addr + (y * game->result.llen + x * \
		(game->result.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_rect(int xy[2], int wh[2], int color, t_game *game)
{
	int i;
	int	j;

	i = 0;
	while (i <= wh[1])
	{
		j = 0;
		while (j <= wh[0])
		{
			if (xy[0] + j >= 0 && xy[0] + j < game->result.width && \
			xy[1] + i >= 0 && xy[1] + i < game->result.height)
				my_mlx_pixel_put(game, xy[0] + j, xy[1] + i, color);
			j++;
		}
		i++;
	}
}

double	to_degrees(double radians)
{
	return (radians * 180.0 / M_PI);
}

double	to_radians(double degrees)
{
	return (degrees / 180.0 * M_PI);
}
