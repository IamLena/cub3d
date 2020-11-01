/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 21:10:18 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:41:01 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "mlx_linux/mlx.h"
# include "structures.h"
# include "errors.h"

# define MAXSREENWIDTH 1920
# define MAXSREENHEIGHT 650
# define FOV 60
# define BUFFER_SIZE 32

/*
** tools1.c
*/
int		exitgame(t_game *game);
int		seterror(t_game *game, int rc, char *msg);
void	seterrorexit(t_game *game, int rc, char *msg);
void	ft_write(const char *str);
int		ft_streq(const char *str1, const char *str2);
/*
** tools2.c
*/
char	*ft_strdup(const char *str);
int		get_next_line(int fd, char **line);
/*
** tools3.c
*/
int		ft_strlen(const char *str);
int		isin(char c, char *str);
int		strends(const char *str, const char *end);
int		strstarts(const char *str, const char *beg);
int		ft_atoi(char **str);
/*
** tools4.c
*/
int		comma_error(char **str);
void	free_matrix(char **matrix, int row_index);
void	put_img(t_game *game);
void	destroy_textures(t_game *game);
int		checkfilename(char *filename, t_game *game);
/*
** tools5.c
*/
int		rgb_to_int(int rgb[3]);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	draw_rect(int xy[2], int wh[2], int color, t_game *game);
double	to_degrees(double radians);
double	to_radians(double degrees);

#endif
