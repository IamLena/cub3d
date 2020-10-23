/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 19:01:02 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/22 13:08:56 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_resolution(t_game *game, char *line, char **msg)
{
	int	width;
	int	height;

	if (game->paramflag & R_FLAG)
	{
		*msg = ft_strdup("resolution is already inputed");
		return (MAPERROR);
	}
	game->paramflag = game->paramflag | R_FLAG;
	width = ft_atoi(&line);
	height = ft_atoi(&line);
	if (width == 0 || height == 0 || *line != '\0')
	{
		*msg = ft_strdup("invalid resolution data");
		return (MAPERROR);
	}
	if (width > 1920)
		width = 1920;
	if (height > 1080)
		height = 1080;
	game->width = width;
	game->height = height;
	return (SUCCESS);
}

static int	get_texture_filename(t_game *game, \
char flag, char *line, char **msg)
{
	if (game->paramflag & flag)
	{
		*msg = ft_strdup("one of textures is attempted for a second input");
		return (MAPERROR);
	}
	game->paramflag = game->paramflag | flag;
	if (flag == NO_FLAG)
		game->no = ft_strdup(line);
	else if (flag == SO_FLAG)
		game->so = ft_strdup(line);
	else if (flag == EA_FLAG)
		game->ea = ft_strdup(line);
	else if (flag == WE_FLAG)
		game->we = ft_strdup(line);
	else
		game->s = ft_strdup(line);
	return (SUCCESS);
}

static int	get_color(t_game *game, char flag, char *line, char **msg)
{
	int	rgb[3];
	int	color;

	*msg = ft_strdup("floor or ceiling color inputed twice");
	if (game->paramflag & flag)
		return (MAPERROR);
	free(*msg);
	game->paramflag = game->paramflag | flag;
	*msg = ft_strdup("invalid color");
	rgb[0] = ft_atoi(&line);
	if (comma_error(&line))
		return (MAPERROR);
	rgb[1] = ft_atoi(&line);
	if (comma_error(&line))
		return (MAPERROR);
	rgb[2] = ft_atoi(&line);
	if (*line != '\0')
		return (MAPERROR);
	if ((color = rgb_to_int(rgb)) == -1)
		return (MAPERROR);
	free(*msg);
	flag == F_FLAG ? (game->f = color) : \
	(game->c = color);
	return (SUCCESS);
}

static int	readmap(t_game *game, char *line, char **msg)
{
	t_map_row	*map;

	map = (t_map_row *)game->map;
	if (append_row(&map, &game->mapwidth, line) == -1)
	{
		free_map(&map);
		*msg = ft_strdup("malloc error");
		return (MAPERROR);
	}
	game->map = map;
	game->mapheight++;
	return (SUCCESS);
}

int			gnl_in_loop(char *line, t_game *game, char **msg)
{
	int	rc;

	if (line[0] == '\0')
		rc = 0;
	else if (strstarts(line, "R "))
		rc = get_resolution(game, line + 2, msg);
	else if (strstarts(line, "NO "))
		rc = get_texture_filename(game, NO_FLAG, line + 3, msg);
	else if (strstarts(line, "SO "))
		rc = get_texture_filename(game, SO_FLAG, line + 3, msg);
	else if (strstarts(line, "WE "))
		rc = get_texture_filename(game, WE_FLAG, line + 3, msg);
	else if (strstarts(line, "EA "))
		rc = get_texture_filename(game, EA_FLAG, line + 3, msg);
	else if (strstarts(line, "S "))
		rc = get_texture_filename(game, S_FLAG, line + 2, msg);
	else if (strstarts(line, "F "))
		rc = get_color(game, F_FLAG, line + 2, msg);
	else if (strstarts(line, "C "))
		rc = get_color(game, C_FLAG, line + 2, msg);
	else if (game->paramflag == ALL_PARAMS)
		rc = readmap(game, line, msg);
	else
		rc = MAPERROR;
	return (rc);
}
