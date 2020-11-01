/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgame.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 21:39:02 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 02:04:32 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITGAME_H
# define INITGAME_H

# include "structures.h"

void	init_game(t_game *game, char *filename);
int		get_resolution(t_game *game, char *line);
int		settexure(t_game *game, char flag, char *line);
int		get_color(t_game *game, char flag, char *line);
int		readmap(t_game *game, char *line);
void	parsemap(t_game *game);
void	parsefile(char *filename, t_game *game);
int		readmaptolist(int fd, t_game *game, char *line);
char	*skipemptylines(int fd, t_game *game);
int		readparams(int fd, t_game *game);
#endif
