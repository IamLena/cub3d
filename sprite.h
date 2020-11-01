/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 01:59:52 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:41:28 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "structures.h"
# include "tools.h"
# include "errors.h"

int			add_sprite(t_sprite **sprites_list, int i, int j, t_texture *tex);
void		sprite_info(t_game *game);
t_sprite	*copy_sprite(t_sprite *origin);
void		free_list(t_sprite *list);
void		draw_sprites(t_game *game);

#endif
