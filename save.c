/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:55:11 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:40:44 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "save.h"
#include "errors.h"
#include "tools.h"
#include "initgame.h"
#include "draw.h"
#include "sprite.h"

void	ft_game_to_image(t_game *game, int fd)
{
	unsigned char	splt_colour[4];
	char			*color;
	int				x;
	int				y;

	y = 0;
	y = game->result.height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < game->result.width)
		{
			color = game->result.addr + (x * 4 + y * game->result.llen);
			splt_colour[0] = (unsigned char)(color[0]);
			splt_colour[1] = (unsigned char)(color[1]);
			splt_colour[2] = (unsigned char)(color[2]);
			splt_colour[3] = (unsigned char)(color[3]);
			write(fd, splt_colour, 4);
			x++;
		}
		y--;
	}
}

void	ft_bzero(void *addr, size_t bytes)
{
	char	*game;
	size_t	i;

	i = 0;
	game = addr;
	while (i < bytes)
	{
		*game = 0;
		game++;
		i++;
	}
}

void	ft_info_header(t_game *game, int fd)
{
	unsigned char	bmih[40];
	int				width;
	int				height;

	ft_bzero(&bmih, 40);
	width = game->result.width;
	height = game->result.height;
	bmih[0] = (unsigned char)(40);
	bmih[4] = (unsigned char)(width);
	bmih[5] = (unsigned char)(width >> 8);
	bmih[6] = (unsigned char)(width >> 16);
	bmih[7] = (unsigned char)(width >> 24);
	bmih[8] = (unsigned char)(height);
	bmih[9] = (unsigned char)(height >> 8);
	bmih[10] = (unsigned char)(height >> 16);
	bmih[11] = (unsigned char)(height >> 24);
	bmih[12] = (unsigned char)(1);
	bmih[14] = (unsigned char)(32);
	write(fd, bmih, 40);
}

void	ft_file_header(t_game *game, int fd)
{
	unsigned char	bmfh[14];
	int				filesize;

	filesize = (game->result.width * game->result.height * 4) + 14 + 40;
	ft_bzero(&bmfh, 14);
	bmfh[0] = 'B';
	bmfh[1] = 'M';
	bmfh[2] = (unsigned char)(filesize);
	bmfh[3] = (unsigned char)(filesize >> 8);
	bmfh[4] = (unsigned char)(filesize >> 16);
	bmfh[4] = (unsigned char)(filesize >> 24);
	bmfh[10] = (unsigned char)(54);
	write(fd, bmfh, 14);
}

void	save_img(t_game *game, char *filename)
{
	int	fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		seterrorexit(game, FILEERROR, "cannot open bmp\n");
	ft_file_header(game, fd);
	ft_info_header(game, fd);
	ft_game_to_image(game, fd);
	close(fd);
}
