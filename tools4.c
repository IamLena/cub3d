/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 00:14:51 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:38:36 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int		comma_error(char **str)
{
	if (str && *str)
	{
		while (**str == ' ' && **str != '\0')
			(*str)++;
		if (**str == ',')
		{
			(*str)++;
			return (0);
		}
	}
	return (1);
}

void	free_matrix(char **matrix, int row_index)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i] && i < row_index)
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

void	put_img(t_game *game)
{
	mlx_put_image_to_window(game->mlx_con, game->window,\
	game->result.img, 0, 0);
}

void	destroy_textures(t_game *game)
{
	if (game->mlx_con)
	{
		if (game->result.img)
			mlx_destroy_image(game->mlx_con, game->result.img);
		if (game->no_tex.img)
			mlx_destroy_image(game->mlx_con, game->no_tex.img);
		if (game->so_tex.img)
			mlx_destroy_image(game->mlx_con, game->so_tex.img);
		if (game->ea_tex.img)
			mlx_destroy_image(game->mlx_con, game->ea_tex.img);
		if (game->we_tex.img)
			mlx_destroy_image(game->mlx_con, game->we_tex.img);
		if (game->s_tex.img)
			mlx_destroy_image(game->mlx_con, game->s_tex.img);
	}
}

int		checkfilename(char *filename, t_game *game)
{
	int		fd;

	if (!strends(filename, ".cub"))
		seterrorexit(game, FILEERROR, "invalid file extention (.cub needed)\n");
	if ((fd = open(filename, O_RDONLY)) == -1)
		seterrorexit(game, FILEERROR, "cannot open file\n");
	return (fd);
}
