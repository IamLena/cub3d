/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 21:10:15 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:39:47 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "sprite.h"

int		exitgame(t_game *game)
{
	if (game->rc)
	{
		ft_write("Error\n");
		ft_write(game->msg);
		free(game->msg);
	}
	if (game->mlx_con && game->window)
		mlx_destroy_window(game->mlx_con, game->window);
	destroy_textures(game);
	free_matrix(game->map, game->mapheight);
	if (game->walls)
		free(game->walls);
	free_list(game->sprites);
	exit(game->rc);
	return (game->rc);
}

int		seterror(t_game *game, int rc, char *msg)
{
	game->rc = rc;
	game->msg = ft_strdup(msg);
	return (rc);
}

void	seterrorexit(t_game *game, int rc, char *msg)
{
	game->rc = rc;
	game->msg = ft_strdup(msg);
	exitgame(game);
}

void	ft_write(const char *str)
{
	int	len;

	len = ft_strlen(str);
	write(1, str, len);
}

int		ft_streq(const char *str1, const char *str2)
{
	if (str1 && str2)
	{
		while (*str1 && *str2 && *str1 == *str2)
		{
			str1++;
			str2++;
		}
		if (*str1 == '\0' && *str2 == '\0')
			return (1);
	}
	return (0);
}
