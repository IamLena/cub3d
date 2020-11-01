/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 21:39:05 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 02:06:55 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initgame.h"
#include "errors.h"
#include "tools.h"
#include "maprow.h"

static void	setzerotex(t_texture *tex)
{
	tex->img = 0;
	tex->addr = 0;
	tex->bpp = 0;
	tex->llen = 0;
	tex->endian = 0;
	tex->width = 0;
	tex->height = 0;
}

static void	setzeros(t_game *game)
{
	game->paramflag = 0;
	game->mlx_con = 0;
	game->window = 0;
	setzerotex(&game->result);
	setzerotex(&game->no_tex);
	setzerotex(&game->so_tex);
	setzerotex(&game->we_tex);
	setzerotex(&game->ea_tex);
	setzerotex(&game->s_tex);
	game->f = 0;
	game->c = 0;
	game->map = 0;
	game->mapwidth = 0;
	game->mapheight = 0;
	game->player_pos.x = -1;
	game->player_pos.y = -1;
	game->view_angle = 0;
	game->sprites = 0;
	game->rc = OK;
	game->msg = 0;
	game->walls = NULL;
}

void		init_game(t_game *game, char *filename)
{
	setzeros(game);
	if (!(game->mlx_con = mlx_init()))
		seterrorexit(game, MLXERROR, "mlx connection failed\n");
	parsefile(filename, game);
	parsemap(game);
	if (!(game->result.img = mlx_new_image(game->mlx_con, \
	game->result.width, game->result.height)))
		seterrorexit(game, MLXERROR, "image creation failed\n");
	if (!(game->result.addr = mlx_get_data_addr(game->result.img, \
	&game->result.bpp, &game->result.llen, &game->result.endian)))
		seterrorexit(game, MLXERROR, "get_data_addr failed\n");
}

void		parsefile(char *filename, t_game *game)
{
	int			fd;
	char		*line;
	t_map_row	*map;

	fd = checkfilename(filename, game);
	if (fd)
	{
		if (readparams(fd, game) || \
		(line = skipemptylines(fd, game)) == NULL \
		|| readmaptolist(fd, game, line))
		{
			close(fd);
			if (game->map)
			{
				map = (t_map_row *)game->map;
				free_map(&map);
				game->map = map;
			}
			exitgame(game);
		}
		close(fd);
	}
}
