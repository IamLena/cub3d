/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 19:33:51 by nalecto           #+#    #+#             */
/*   Updated: 2020/09/17 17:22:27 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int borderend(char *line, char **msg)
{
	int len = ft_strlen(line) - 1;
	while (line[len] == ' ')
		len--;
	if (len >= 0 && line[len] != '1')
	{
		*msg = ft_strdup("not closed map borders");
		return (0);
	}
	return (1);
}

int symbol_ok(char **map, t_game *game, int i, int j, char **msg)
{
	if (!isin(map[i][j], " 012NSEW"))
	{
		*msg = ft_strdup("invalid symbol in map content");
		return (0);
	}
	if ((i == 0 || i == game->mapheight || j == 0) && !isin(map[i][j], " 1"))
	{
		*msg = ft_strdup("not closed map borders");
		return (0);
	}
	if (isin(map[i][j], "02NSWE") && (map[i][j-1] == ' ' || map[i-1][j] == ' '))
	{
		*msg = ft_strdup("map is not closed inside");
		return (0);
	}
	if (isin(map[i][j], "NSWE") && game->player_pos.x != -1)
	{
		*msg = ft_strdup("too many players");
		return (0);
	}
	return (1);
}

int parsemap(t_game *game, char **msg)
{
	char **map;
	t_map_row *listmap;
	t_map_row * listmap_head;
	int i;
	int j;

	map = (char **)malloc((game->mapheight + 1) * sizeof(char *));
	if (map)
	{
		listmap = (t_map_row *)game->map;
		listmap_head = listmap;
		i = 0;
		while (listmap)
		{
			map[i] = malloc(game->mapwidth + 1);
			if (map[i]) {
				j = 0;
				while (listmap->line[j] != '\0')
				{
					map[i][j] = listmap->line[j];
					if (!borderend(listmap->line, msg) || !symbol_ok(map, game, i, j, msg))
					{
						free_matrix(map, i);
						free_map(&listmap_head);
						game->map = NULL;
						return (MAPERROR);
					}
					if (isin(map[i][j], "NSWE"))
					{
						game->player_pos.x = j + 0.5;
						game->player_pos.y = i + 0.5;
						// if (map[i][j] == 'N')
						// 	game->view_angle = 270;
						// else if (map[i][j] == 'E')
						// 	game->view_angle = 0;
						// else if (map[i][j] == 'S')
						// 	game->view_angle = 90;
						// else
						// 	game->view_angle = 180;
						//wrong
						if (map[i][j] == 'N')
							game->view_angle = 0;
						else if (map[i][j] == 'E')
							game->view_angle = 90;
						else if (map[i][j] == 'S')
							game->view_angle = 180;
						else
							game->view_angle = 270;
					}
					j++;
				}
				while (j < game->mapwidth)
				{
					map[i][j] = ' ';
					j++;
				}
				map[i][j] = '\0';
			}
			i++;
			listmap = listmap->next;
		}
		map[i] = NULL;
	}
	game->map = map;
	return 0;
}