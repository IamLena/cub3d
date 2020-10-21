/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 15:33:16 by nalecto           #+#    #+#             */
/*   Updated: 2020/09/14 16:49:05 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include <math.h>
# include "cubstruct.h"
# define SCALE   1
# define FOV    65
// # define RAYS   512
# define WIN_H 250

int rgb_to_int(int r, int g, int b);
void my_mlx_pixel_put(t_game *game, int x, int y, int color);
void draw_square(int x, int y, int width, int color, t_game *game);
void draw_rect(int x, int y, int width, int height, int color, t_game *game);
double to_degrees(double radians);
double to_radians(double degrees);
void put_img(t_game *game);


#endif