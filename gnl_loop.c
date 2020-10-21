/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 19:01:02 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/21 12:27:36 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int get_resolution(t_game *game, char *line, char **msg)
{
	int width;
	int height;

	if (game->paramflag & R_FLAG)
	{
		*msg = ft_strdup("resolution is already inputed");
		return MAPERROR;
	}
	game->paramflag = game->paramflag | R_FLAG;
	width = ft_atoi(&line);
	height = ft_atoi(&line);
	if (width == 0 || height == 0 || *line != '\0')
	{
		*msg = ft_strdup("invalid resolution data");
		return MAPERROR;
	}
	game->width = width;
	game->height = height;
	return (SUCCESS);
}

static int get_north_texture(t_game *game, char *line, char **msg)
{
	if (game->paramflag & NO_FLAG)
	{
		*msg = ft_strdup("north texture is already inputed");
		return MAPERROR;
	}
	game->paramflag = game->paramflag | NO_FLAG;
	game->no = ft_strdup(line);
	return (SUCCESS);
}

static int get_south_texture(t_game *game, char *line, char **msg)
{
	if (game->paramflag & SO_FLAG)
	{
		*msg = ft_strdup("south texture is already inputed");
		return MAPERROR;
	}
	game->paramflag = game->paramflag | SO_FLAG;
	game->so = ft_strdup(line);
	return (SUCCESS);
}

static int get_west_texture(t_game *game, char *line, char **msg)
{
	if (game->paramflag & WE_FLAG)
	{
		*msg = ft_strdup("west texture is already inputed");
		return MAPERROR;
	}
	game->paramflag = game->paramflag | WE_FLAG;
	game->we = ft_strdup(line);
	return (SUCCESS);
}

static int get_east_texture(t_game *game, char *line, char **msg)
{
	if (game->paramflag & EA_FLAG)
	{
		*msg = ft_strdup("east texture is already inputed");
		return MAPERROR;
	}
	game->paramflag = game->paramflag | EA_FLAG;
	game->ea = ft_strdup(line);
	return (SUCCESS);
}

static int get_sprite_texture(t_game *game, char *line, char **msg)
{
	if (game->paramflag & S_FLAG)
	{
		*msg = ft_strdup("sprite texture is already inputed");
		return MAPERROR;
	}
	game->paramflag = game->paramflag | S_FLAG;
	game->s = ft_strdup(line);
	return (SUCCESS);
}

static int get_color(char *line, char **msg, int *color)
{
    int r;
	int g;
	int b;

	r = ft_atoi(&line);
	if (!comma_error(&line))
    {
        g = ft_atoi(&line);
        if (!comma_error(&line))
        {
            b = ft_atoi(&line);
            if (*line == '\0')
                if ((*color = rgb_to_int(r, g, b)) != -1)
                    return (SUCCESS);
        }
    }
	*msg = ft_strdup("invalid color");
	return (MAPERROR);
}

static int get_floor_color(t_game *game, char *line, char **msg)
{
	//errors on dubles
    int color;
	if (get_color(line, msg, &color) != MAPERROR)
    {
        game->f = color;
        return (SUCCESS);
    }
    return (MAPERROR);
}

static int get_ceiling_color(t_game *game, char *line, char **msg)
{
	int color;
	if (get_color(line, msg, &color) != MAPERROR)
    {
        game->c = color;
        return (SUCCESS);
    }
    return (MAPERROR);
}

static int readmap(t_game *game, char *line, char **msg)
{
	t_map_row *map = (t_map_row *)game->map;
	if (append_row(&map, &game->mapwidth, line) == -1)
	{
		free_map(&map);
		*msg = ft_strdup("malloc error");
		return(MAPERROR);
	}
	game->map = map;
	game->mapheight++;
	return (SUCCESS);
}

int gnl_in_loop(char *line, t_game *game, char **msg)
{
	int rc;
	if (line[0] == '\0')
		rc = 0;
	else if (strstarts(line, "R "))
		rc = get_resolution(game, line + 2, msg);
	else if (strstarts(line, "NO "))
		rc = get_north_texture(game, line + 3, msg);
	else if (strstarts(line, "SO "))
		rc = get_south_texture(game, line + 3, msg);
	else if (strstarts(line, "WE "))
		rc = get_west_texture(game, line + 3, msg);
	else if (strstarts(line, "EA "))
		rc = get_east_texture(game, line + 3, msg);
	else if (strstarts(line, "S "))
		rc = get_sprite_texture(game, line + 2, msg);
	else if (strstarts(line, "F "))
		rc = get_floor_color(game, line + 2, msg);
	else if (strstarts(line, "C "))
		rc = get_ceiling_color(game, line + 2, msg);
	else if(game->paramflag == ALL_PARAMS)
		rc = readmap(game, line, msg);
	else
		rc = MAPERROR;
	return (rc);
}
