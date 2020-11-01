/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 14:50:38 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/28 19:19:58 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "structures.h"
# include "tools.h"
# include "errors.h"

t_wall_inter	get_side(double angle, double plpos[2], t_game *game);
void			get_wall_intersections(t_game *game);
void			draw_walls(t_game *game);

#endif
