/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturetry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 12:32:19 by nalecto           #+#    #+#             */
/*   Updated: 2020/09/24 15:24:34 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 400
#define HEIGHT 300
#define NAME "my cub3D"

typedef struct s_data {
	void *img;
	char *addr;
	int bpp;
	int llen;
	int endian;
	int width;
	int height;
} t_data;

typedef struct s_vars{
	void *mlx_con;
	void *window;
} t_vars;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->llen + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_square(int x, int y, int width, int color, t_data *data)
{
    int i, j;
    
    i = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			my_mlx_pixel_put(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// int close(t_vars *vars)
// {
// 	mlx_clear_window (vars->mlx_con, vars->window);
// 	mlx_destroy_window(vars->mlx_con, vars->window);
// 	exit(0);
// 	return 0;
// }

int main(void)
{
    t_vars vars;
	t_data img;
    t_data tex;

	vars.mlx_con = mlx_init();
	if (!vars.mlx_con)
		perror("mlx connection failed");
	vars.window = mlx_new_window(vars.mlx_con, 1000, 1000, NAME);
	if (!vars.window)
		perror("window creation failed");

    tex.img = mlx_xpm_file_to_image(vars.mlx_con, "textures/wall3.xpm", &tex.width, &tex.height);
    tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.llen, &tex.endian);

	int scale = 8;

	img.img = mlx_new_image(vars.mlx_con, tex.width * scale, tex.height * scale);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.endian);

	int color;
	
	int i = 0;
	while (i < tex.height)
	{
		int j = 0;
		while(j < tex.width)
		{
			color = *(int*)(tex.addr + (4 * tex.width * i) + (4 * j));
			draw_square(i * scale, j * scale, scale, color, &img);
			j++;
		}
		i++;
	}
	
	mlx_put_image_to_window(vars.mlx_con, vars.window, img.img, 0, 0);

    // mlx_hook(vars.window, 17, 0L, close, &vars);
	mlx_loop(vars.mlx_con);
	return 0;
}

