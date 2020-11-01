/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:41:10 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/31 16:19:47 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initgame.h"
#include "maprow.h"
#include "sprite.h"
#include "errors.h"

static int	bad_symbol(char **map, t_game *game, int i, int j)
{
	if (!isin(map[i][j], " 012NSEW"))
		return (seterror(game, MAPERROR, "invalid symbol in map content\n"));
	if ((i == 0 || i == game->mapheight - 1) && !isin(map[i][j], " 1"))
		return (seterror(game, MAPERROR, "not closed map borders\n"));
	if (isin(map[i][j], "02NSWE") && (map[i][j - 1] == ' ' \
	|| map[i - 1][j] == ' '))
		return (seterror(game, MAPERROR, "map is not closed inside\n"));
	if (isin(map[i][j], "NSWE") && game->player_pos.x != -1)
		return (seterror(game, MAPERROR, "too many players\n"));
	return (0);
}

static void	init_player(t_game *game, char pos, int i, int j)
{
	game->player_pos.x = j + 0.5;
	game->player_pos.y = i + 0.5;
	if (pos == 'N')
		game->view_angle = 0;
	else if (pos == 'E')
		game->view_angle = 90;
	else if (pos == 'S')
		game->view_angle = 180;
	else
		game->view_angle = 270;
}

static int	check_set_row(int i, t_map_row *listmap, char **map, t_game *game)
{
	int	j;

	j = -1;
	while (listmap->line[++j] != '\0')
	{
		map[i][j] = listmap->line[j];
		if (bad_symbol(map, game, i, j) || \
		(map[i][j] == '2' && add_sprite(&game->sprites, i, j, &game->s_tex)))
		{
			if (!game->rc)
				seterror(game, MEMERROR, "malloc error in add sprite\n");
			free_matrix(map, i + 1);
			game->map = NULL;
			return (1);
		}
		if (isin(map[i][j], "NSWE"))
			init_player(game, map[i][j], i, j);
	}
	while (j < game->mapwidth)
		map[i][j++] = ' ';
	map[i][j] = '\0';
	return (0);
}

static int	setmap(char **map, t_game *game)
{
	t_map_row	*listmap;
	int			i;

	i = 0;
	listmap = (t_map_row *)game->map;
	while (listmap)
	{
		map[i] = malloc(game->mapwidth + 1);
		if (map[i])
		{
			if (check_set_row(i, listmap, map, game) != 0)
				return (1);
		}
		else
			return (seterror(game, MAPERROR, "malloc error\n"));
		i++;
		listmap = listmap->next;
	}
	map[i] = NULL;
	return (0);
}

void		parsemap(t_game *game)
{
	char		**map;
	t_map_row	*listmap_head;

	listmap_head = (t_map_row *)game->map;
	map = (char **)malloc((game->mapheight + 1) * sizeof(char *));
	if (map)
	{
		if (setmap(map, game) != 0)
		{
			free_map(&listmap_head);
			exitgame(game);
		}
	}
	else
	{
		free_map(&listmap_head);
		seterrorexit(game, MAPERROR, "malloc error\n");
	}
	free_map(&listmap_head);
	game->map = map;
	if (game->player_pos.x == -1)
		seterrorexit(game, MAPERROR, "no player on the map\n");
}
