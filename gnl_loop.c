/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:40:20 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 02:00:32 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initgame.h"
#include "errors.h"
#include "tools.h"
#include "maprow.h"

int	get_resolution(t_game *game, char *line)
{
	int	width;
	int	height;

	if (game->paramflag & R_FLAG)
		return (seterror(game, MAPERROR, "resolution is already inputed\n"));
	game->paramflag = game->paramflag | R_FLAG;
	if ((width = ft_atoi(&line)) == 0 || \
	(height = ft_atoi(&line)) == 0 || *line != '\0')
		return (seterror(game, MAPERROR, "invalid resolution data\n"));
	if (width > MAXSREENWIDTH)
		width = MAXSREENWIDTH;
	if (height > MAXSREENHEIGHT)
		height = MAXSREENHEIGHT;
	game->result.width = width;
	game->result.height = height;
	return (OK);
}

int	settexure(t_game *game, char flag, char *line)
{
	t_texture	tex;

	if (game->paramflag & flag)
		return (seterror(game, MAPERROR, "second input of same wall\n"));
	game->paramflag = game->paramflag | flag;
	tex.img = mlx_xpm_file_to_image(game->mlx_con, line, &tex.width, \
	&tex.height);
	if (tex.img)
		tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.llen, \
		&tex.endian);
	if (!tex.img || !tex.addr)
		return (seterror(game, MAPERROR, "texture input error\n"));
	if (flag == NO_FLAG)
		game->no_tex = tex;
	else if (flag == SO_FLAG)
		game->so_tex = tex;
	else if (flag == EA_FLAG)
		game->ea_tex = tex;
	else if (flag == WE_FLAG)
		game->we_tex = tex;
	else
		game->s_tex = tex;
	return (OK);
}

int	get_color(t_game *game, char flag, char *line)
{
	int	rgb[3];
	int	color;

	if (game->paramflag & flag)
	{
		return (seterror(game, MAPERROR, \
		"floor or ceiling color inputed twice\n"));
	}
	game->paramflag = (game->paramflag) | flag;
	rgb[0] = ft_atoi(&line);
	if (comma_error(&line))
		return (seterror(game, MAPERROR, "invalid color\n"));
	rgb[1] = ft_atoi(&line);
	if (comma_error(&line))
		return (seterror(game, MAPERROR, "invalid color\n"));
	rgb[2] = ft_atoi(&line);
	if (*line != '\0')
		return (seterror(game, MAPERROR, "invalid color\n"));
	if ((color = rgb_to_int(rgb)) == -1)
		return (seterror(game, MAPERROR, "invalid color\n"));
	flag == F_FLAG ? (game->f = color) : \
	(game->c = color);
	return (OK);
}

int	readmap(t_game *game, char *line)
{
	t_map_row	*map;

	map = (t_map_row *)game->map;
	if (!borderokay(line))
	{
		free_map(&map);
		game->map = map;
		return (seterror(game, MAPERROR, "map is not closed\n"));
	}
	if (append_row(&map, &game->mapwidth, line) == -1)
	{
		free_map(&map);
		game->map = map;
		return (seterror(game, MAPERROR, "malloc error\n"));
	}
	game->map = map;
	game->mapheight++;
	return (OK);
}
