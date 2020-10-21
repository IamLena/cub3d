/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:49:43 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/21 12:43:07 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture settexture(void *mlx_con, char *filename)
{
	t_texture tex;
	tex.img = mlx_xpm_file_to_image(mlx_con, filename, &tex.width, &tex.height);
    if (tex.img)
		tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.llen, &tex.endian);
	return tex;
}

static int gameconfig(int fd, t_game *game, char **msg)
{
	char *line;
	int rc;

	rc = 0;
	while (get_next_line(fd, &line))
		if ((rc = gnl_in_loop(line, game, msg)))
			return (rc);
	rc = gnl_in_loop(line, game, msg);
	if (game->paramflag != ALL_PARAMS)
	{
		*msg = ft_strdup("not all data is provided");
		rc = MAPERROR;
	}
	free(line);
	return (rc);
}

static void parsefile(char *filename, t_game *game)
{
	int fd;
	char *line;
	char *msg;
	int rc;

	if (!strends(filename, ".cub"))
		errorexit(FILEERROR, "invalid file extention (.cub needed)", 0);
	if (!(fd = open(filename, O_RDONLY)))
		errorexit(FILEERROR, "cannot open file", 0);
	rc = gameconfig(fd, game, &msg);
	close(fd);
	if (rc)
		errorexit(rc, msg, 1);
	// print_map(game->map);
	rc = parsemap(game, &msg);
	if (rc)
		errorexit(rc, msg, 1);
	// print_matrix(game->map);
}

static void setzeros1(t_game *game)
{
	game->paramflag = 0;
	game->width = 0;
	game->height = 0;
	game->no = 0;
	game->so = 0;
	game->we = 0;
	game->ea = 0;
	game->s = 0;
	game->f = 0;
	game->c = 0;
	game->map = NULL;
	game->mapwidth = 0;
	game->mapheight = 0;
	game->player_pos.x = -1;
	game->player_pos.y = -1;
	game->view_angle = 0;
}

static void setzeros2(t_game *game)
{
	game->mlx_con = 0;
	game->window = 0;
	game->img = 0;
	game->imgadr = 0;
	game->bpp = 0;
	game->llen = 0;
	game->endian = 0;
}

void init_game(char *filename, t_game *game)
{
	setzeros1(game);
	setzeros2(game);
	parsefile(filename, game);
	if (!(game->mlx_con = mlx_init()))
		errorexit(MLXERROR, "mlx connection failed", 0);
	if (!(game->window = mlx_new_window(game->mlx_con, game->width, game->height, NAME)))
		errorexit(MLXERROR, "window creation failed", 0);
	if (!(game->img = mlx_new_image(game->mlx_con, game->width, game->height)))
		errorexit(MLXERROR, "image creation failed", 0);
	if (!(game->imgadr = mlx_get_data_addr(game->img, &game->bpp, &game->llen, &game->endian)))
		errorexit(MLXERROR, "get_data_addr failed", 0);
	game->no_tex = settexture(game->mlx_con, game->no);
	if (!game->no_tex.img)
		errorexit(MAPERROR, "north xpm file error", 0);
	game->so_tex = settexture(game->mlx_con, game->so);
	if (!game->so_tex.img)
		errorexit(MAPERROR, "south xpm file error", 0);
	game->we_tex = settexture(game->mlx_con, game->we);
	if (!game->we_tex.img)
		errorexit(MAPERROR, "west xpm file error", 0);
	game->ea_tex = settexture(game->mlx_con, game->ea);
	if (!game->ea_tex.img)
		errorexit(MAPERROR, "east xpm file error", 0);
	game->s_tex = settexture(game->mlx_con, game->s);
	if (!game->s_tex.img)
		errorexit(MAPERROR, "sprite xpm file error", 0);
}
