/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:39:42 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/23 18:30:03 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_tools.h"
#include "sprite.h"

t_wall_inter get_side(double angle, float plx, float ply)
{
    double sin_an = sin(to_radians(angle));
    double cos_an = cos(to_radians(angle));
    t_wall_inter intersect;
    intersect.dist = 2;

    if (cos_an > 0)
    {
        intersect.dist = (ply - ceil(ply) + 1) / cos_an; //south
        intersect.x = plx + intersect.dist * sin_an;
        intersect.y = ceil(ply) - 1;
        intersect.type = SO_FLAG;
        intersect.i = intersect.y - 1;
        intersect.j = floor(intersect.x);
        intersect.tex_w = intersect.x - floor(intersect.x);
    }
    else if (cos_an < 0)
    {
        intersect.dist = (ply - floor(ply) - 1) / cos_an; //north
        intersect.x = plx + intersect.dist * sin_an;
        intersect.y = floor(ply) + 1;
        intersect.type = NO_FLAG;
        intersect.color = 0x0000FF00;
        intersect.i = intersect.y;
        intersect.j = floor(intersect.x);
        intersect.tex_w = ceil(intersect.x) - intersect.x;
    }
    if (sin_an > 0 && (floor(plx) + 1 - plx) / sin_an < intersect.dist)
    {
        intersect.dist = (floor(plx) + 1 - plx) / sin_an; //west
        intersect.x = floor(plx) + 1;
        intersect.y = ply - intersect.dist * cos_an;
        intersect.color = 0x000000FF;
        intersect.type = WE_FLAG;
        intersect.i = floor(intersect.y);
        intersect.j = intersect.x;
        intersect.tex_w = intersect.y - floor(intersect.y);
    }
    else if (sin_an < 0 && (ceil(plx) - 1 - plx) / sin_an < intersect.dist)
    {
        intersect.dist = (ceil(plx) - 1 - plx) / sin_an; //east
        intersect.x = ceil(plx) - 1;
        intersect.y = ply - intersect.dist * cos_an;
        intersect.color = 0x00FFFFFF;
        intersect.type = EA_FLAG;
        intersect.i = floor(intersect.y);
        intersect.j = intersect.x - 1;
        intersect.tex_w = ceil(intersect.y) - intersect.y;
    }

    return intersect;
}

t_wall_inter manage_fence(double angle, t_game *game)
{
    float plx = game->player_pos.x;
    float ply = game->player_pos.y;
    char **map = (char **)game->map;
    t_wall_inter intersect;
    double dist_to_wall = 0;

    while (plx > 0 && ply > 0 && plx < game->mapwidth && ply < game->mapheight)
    {
        intersect = get_side(angle, plx, ply);
        dist_to_wall += intersect.dist;
        if (map[intersect.i][intersect.j] == '1')
        {
            intersect.height =  WIN_H / (dist_to_wall * cos(to_radians(angle - game->view_angle)));
            return intersect;
        }
        else if (map[intersect.i][intersect.j] == '2')
        {
            saw_sprite(game->sprites, intersect.i, intersect.j);
        }
        plx = intersect.x;
        ply = intersect.y;
    }
    return intersect;
}

// int draw_line(int x, t_game *game, t_wall_inter inter)
// {
//     int horizon = game->height / 2;
//     draw_rect(x, 0, 1, horizon - inter.height / 2, game->c, game);
//     int pixel = 0;
//     int xx = inter.tex_w * game->so_tex.width;
//     double height_scale = inter.height / game->so_tex.height;
//     while (pixel < game->so_tex.height)
//     {
//         int k = 0;
//         int color = *(int*)(game->so_tex.addr + (4 * game->so_tex.width * pixel) + (4 * xx));
//         while (k < height_scale)
//         {
//             my_mlx_pixel_put(game, x, (int)(horizon - inter.height / 2 + pixel * height_scale + k), color);
//             k++;
//         }
//         pixel++;
//     }
//     draw_rect(x, horizon + inter.height / 2, 1, horizon - inter.height / 2, game->f, game);
// }

int draw_walls(t_game *game)
{
    float dist;
    double x, y;
    int cnt = 0;
    double anglestep = (double)FOV / (double)game->width;
    double angle = game->view_angle - FOV / 2;
    char **map = game->map;
    int horizon = game->height / 2;

    draw_rect(0, 0, game->width, horizon, game->c, game);
    draw_rect(0, horizon, game->width, horizon, game->f, game);

    double height;
    int color;
    while(cnt < game->width)
    {
        t_wall_inter inter = manage_fence(angle, game);
        if (inter.type == SO_FLAG)
        {
            int pixel = 0;
            int x = inter.tex_w * game->so_tex.width;
            double height_scale = inter.height / game->so_tex.height;
            while (pixel < game->so_tex.height)
            {
                int k = 0;
                int color = *(int*)(game->so_tex.addr + (4 * game->so_tex.width * pixel) + (4 * x));
                while (k < height_scale)
                {
                    my_mlx_pixel_put(game, cnt, (int)(horizon - inter.height / 2 + pixel * height_scale + k), color);
                    k++;
                }
                pixel++;
            }
        }
        else if (inter.type == NO_FLAG)
        {
            int pixel = 0;
            int x = inter.tex_w * game->no_tex.width;
            double height_scale = inter.height / game->no_tex.height;
            while (pixel < game->no_tex.height)
            {
                int k = 0;
                int color = *(int*)(game->no_tex.addr + (4 * game->no_tex.width * pixel) + (4 * x));
                while (k < height_scale)
                {
                    my_mlx_pixel_put(game, cnt, (int)(horizon - inter.height / 2 + pixel * height_scale + k), color);
                    k++;
                }
                pixel++;
            }
        }
        else if (inter.type == WE_FLAG)
        {
            int pixel = 0;
            int x = inter.tex_w * game->we_tex.width;
            double height_scale = inter.height / game->we_tex.height;
            while (pixel < game->we_tex.height)
            {
                int k = 0;
                int color = *(int*)(game->we_tex.addr + (4 * game->we_tex.width * pixel) + (4 * x));
                while (k < height_scale)
                {
                    my_mlx_pixel_put(game, cnt, (int)(horizon - inter.height / 2 + pixel * height_scale + k), color);
                    k++;
                }
                pixel++;
            }
        }
        else if (inter.type == EA_FLAG)
        {
            int pixel = 0;
            int x = inter.tex_w * game->ea_tex.width;
            double height_scale = inter.height / game->ea_tex.height;
            while (pixel < game->ea_tex.height)
            {
                int k = 0;
                int color = *(int*)(game->ea_tex.addr + (4 * game->ea_tex.width * pixel) + (4 * x));
                while (k < height_scale)
                {
                    my_mlx_pixel_put(game, cnt, (int)(horizon - inter.height / 2 + pixel * height_scale + k), color);
                    k++;
                }
                pixel++;
            }
        }
        else
        {
            if (inter.height > game->height)
            inter.height = game->height;
            draw_rect(cnt, horizon - inter.height / 2, 1, inter.height , 0, game);
        }
        cnt++;
        angle += anglestep;
    }
    return (0);
}

int draw_map(t_game *game)
{
    draw_walls(game);
    draw_sprite(game);
}
