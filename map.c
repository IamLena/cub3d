/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 19:33:51 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/22 22:07:42 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	borderends(char *line, char **msg)
{
	int	len;
	int	i;

	len = ft_strlen(line) - 1;
	i = 0;
	while (i >= 0 && line[i] == ' ')
		i++;
	if (line[i] != '1')
	{
		*msg = ft_strdup("not closed map borders");
		return (0);
	}
	while (len >= 0 && line[len] == ' ')
		len--;
	if (len >= 0 && line[len] != '1')
	{
		*msg = ft_strdup("not closed map borders");
		return (0);
	}
	return (1);
}

static int	symbol_ok(char **map, t_game *game, int i, int j, char **msg)
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

int			parsemap(t_game *game, char **msg)
{
	char		**map;
	t_map_row	*listmap;
	t_map_row	*listmap_head;
	int			i;
	int			j;

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
					if (!borderends(listmap->line, msg) || !symbol_ok(map, game, i, j, msg))
					{
						free_matrix(map, i);
						free_map(&listmap_head);
						game->map = NULL;
						return (MAPERROR);
					}
					if (isin(map[i][j], "NSWE"))
						init_player(game, map[i][j], i, j);
					if (map[i][j] == '2')
					{
						add_sprite(&game->sprites, i, j);
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
			else
			{
				// malloc error
				free_map(&listmap_head);
				*msg = ft_strdup("malloc error");
				game->map = NULL;
				return (MAPERROR);
			}
			i++;
			listmap = listmap->next;
		}
		map[i] = NULL;
	}
	game->map = map;
	return 0;
}
