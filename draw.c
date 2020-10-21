/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:39:42 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/21 14:06:05 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_tools.h"

int draw_walls(t_game *game);

int get_scale_2d(t_game *game)
{
    int wd;
    int hd;
    int scale;

    wd = game->width / game->mapwidth;
    hd = game->height / game->mapheight;
    scale = wd < hd ? wd : hd;
    return scale;
}

int draw_2dmap(t_game *game)
{
    int i;
    int j;
    int color;
    char **map = game->map;
    int scale = get_scale_2d(game);

    i = 0;
    while (i < game->mapheight)
    {
        j = 0;
        while (j < game->mapwidth)
        {
            if (map[i][j]== ' ')
                color = 0x00000000;
            else if (map[i][j]== '0')
                color = 0x00008700;
            else if (map[i][j]== '1')
                color = 0x00555555;
            else if (map[i][j]== '2')
                color = 0x00FF0000;
            else
                color = 0x00FFFFFF;
            draw_square(j * scale, i * scale, scale, color, game);
            j++;
        }
        i++;
    }
}

int draw_vision(t_game *game)
{
    float dist;
    float x, y;
    int cnt = 0;
    double anglestep = (double)FOV / (double)game->width;
    double angle = game->view_angle - FOV / 2;
    char **map = game->map;
    int scale = get_scale_2d(game);

    while(cnt < game->width)
    {
        dist = 0;
        while (dist < 10)
        {
            x = game->player_pos.x + dist * cos(to_radians(angle));
            y = game->player_pos.y + dist * sin(to_radians(angle));
            // if (map[(int)y][(int)x] == '1')
            if (map[(int)round(y)][(int)round(x)] != '1')
                break;
            draw_square(x * scale, y * scale, 1, 0x000000FF , game);
            dist += 0.2;
        }
        cnt++;
        angle += anglestep;
    }
    return (0);
}

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
        intersect.color = 0x0000FF00;
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
        plx = intersect.x;
        ply = intersect.y;
    }
    return intersect;
}

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
            // int height_scale = inter.height / game->so_tex.height;
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
            // int height_scale = inter.height / game->no_tex.height;
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
            // int height_scale = inter.height / game->we_tex.height;
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
            // int height_scale = inter.height / game->ea_tex.height;
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
            draw_rect(cnt, horizon - inter.height / 2, 1, inter.height , inter.color, game);
        }
        cnt++;
        angle += anglestep;
    }
    return (0);
}

int draw_map(t_game *game)
{
    // draw_2dmap(game);
    // draw_vision(game);
    draw_walls(game);
    put_img(game);
}
