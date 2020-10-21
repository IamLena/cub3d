/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 12:32:19 by nalecto           #+#    #+#             */
/*   Updated: 2020/09/03 15:34:19 by nalecto          ###   ########.fr       */
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
} t_data;

typedef struct s_vars{
	void *mlx_con;
	void *window;
} t_vars;

typedef struct s_obj {
	int x;
	int y;
	int width;
	t_data *data;
	void *mlx_con;
	void *window;
	int flag;
} t_obj;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x < WIDTH && y < HEIGHT)
	{
		dst = data->addr + (y * data->llen + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int close(t_vars *vars)
{
	mlx_clear_window (vars->mlx_con, vars->window);
	mlx_destroy_window(vars->mlx_con, vars->window);
	exit(0);
	return 0;
}

int startmove(int keycode, t_obj *obj)
{
	if (keycode == 53) {
		mlx_clear_window (obj->mlx_con, obj->window);
		mlx_destroy_window(obj->mlx_con, obj->window);
		exit(0);
	}
	else
		obj->flag = 1;
	return 0;
}

int stopmove(int keycode, t_obj *obj)
{
	if(keycode != 53)
		obj->flag = 0;
	return 0;
}

int render(void *object)
{
	t_obj *obj = (t_obj*)object;
	int i;
	int j;

	int color = 0x00FF0000;
	if (obj->flag)
	{
		i = 0;
		while (i < obj->width)
		{
			j = 0;
			while (j < obj->width)
			{
				// if (obj->x > WIDTH)
				// 	obj->x = 5;
				// if (obj->y > HEIGHT)
				// 	obj->y = HEIGHT ;
				//mlx_clear_window(obj->mlx_con, obj->window);
				//mlx_destroy_image(obj->mlx_con, obj->data->img);
				my_mlx_pixel_put(obj->data, (obj->x + j) % WIDTH, (obj->y + i) % HEIGHT, color);
				mlx_put_image_to_window(obj->mlx_con, obj->window, obj->data->img, 0, 0);
				j++;
			}
			i++;
			//printf("%d %d\n", obj->x, obj->y);
		}
		obj->x += 30;
	}
	return 0;
}

int main(void)
{
	void *mlx_con;
	void *window;
	t_data img;
	t_vars vars;
	t_obj object;

	object.x = 5;
	object.y = 5;
	object.width = 20;
	object.flag = 0;

	mlx_con = mlx_init();
	if (!mlx_con)
		perror("mlx connection failed");
	window = mlx_new_window(mlx_con, WIDTH, HEIGHT, NAME);
	if (!window)
		perror("window creation failed");
	img.img = mlx_new_image(mlx_con, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// mlx_put_image_to_window(mlx_con, window, img.img, 0, 0);
	object.data = &img;
	object.window = window;
	object.mlx_con = mlx_con;
	vars.window = window;
	vars.mlx_con = mlx_con;
	//mlx_key_hook(vars.window, close, &vars);

	// render(&object);
	// mlx_put_image_to_window(mlx_con, window, img.img, 0, 0);
	mlx_loop_hook(mlx_con, render, &object);
	//mlx_hook(vars.window, 2, 1L<<0, close, &vars);
	mlx_hook(vars.window, 2, 1L<<0, startmove, &object);
	mlx_hook(vars.window, 3, 1L<<1, stopmove, &object);
	mlx_hook(vars.window, 17, 0L, close, &vars);
	mlx_loop(mlx_con);
	return 0;
}
