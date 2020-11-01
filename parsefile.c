/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 02:02:46 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 12:43:10 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initgame.h"
#include "errors.h"
#include "tools.h"
#include "maprow.h"

void	ifelsesforreadparams(t_game *game, char *line)
{
	if (strstarts(line, "R "))
		get_resolution(game, line + 2);
	else if (strstarts(line, "NO "))
		settexure(game, NO_FLAG, line + 3);
	else if (strstarts(line, "SO "))
		settexure(game, SO_FLAG, line + 3);
	else if (strstarts(line, "WE "))
		settexure(game, WE_FLAG, line + 3);
	else if (strstarts(line, "EA "))
		settexure(game, EA_FLAG, line + 3);
	else if (strstarts(line, "S "))
		settexure(game, S_FLAG, line + 2);
	else if (strstarts(line, "F "))
		get_color(game, F_FLAG, line + 2);
	else if (strstarts(line, "C "))
		get_color(game, C_FLAG, line + 2);
	else if (line[0] != '\0')
		seterror(game, MAPERROR, "invalid cub file\n");
}

int		readparams(int fd, t_game *game)
{
	char	*line;

	while (!game->rc && game->paramflag != ALL_PARAMS \
	&& get_next_line(fd, &line))
	{
		ifelsesforreadparams(game, line);
		free(line);
		line = NULL;
	}
	if (line != NULL)
	{
		free(line);
		seterror(game, MAPERROR, "invalid cub file\n");
	}
	return (game->rc);
}

char	*skipemptylines(int fd, t_game *game)
{
	char	*line;

	while (!game->rc && get_next_line(fd, &line) && line[0] == '\0')
	{
		free(line);
		line = NULL;
	}
	if (!game->rc && line && line[0] == '\0')
	{
		free(line);
		line = NULL;
		seterror(game, MAPERROR, "there is no map\n");
	}
	return (line);
}

void	inloopforreadmaptolist(t_game *game, char **line, int *empty_flag)
{
	if (**line == '\0')
		*empty_flag = 1;
	else if (!*empty_flag)
		readmap(game, *line);
	else
		seterror(game, MAPERROR, "empty line in map content\n");
	free(*line);
	*line = NULL;
}

int		readmaptolist(int fd, t_game *game, char *line)
{
	int empty_flag;

	empty_flag = 0;
	readmap(game, line);
	if (line)
	{
		free(line);
		line = NULL;
	}
	while (!game->rc && get_next_line(fd, &line))
	{
		inloopforreadmaptolist(game, &line, &empty_flag);
	}
	if (!game->rc && line)
		inloopforreadmaptolist(game, &line, &empty_flag);
	return (game->rc);
}
