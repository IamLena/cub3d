/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 01:46:51 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:40:38 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAVE_H
# define SAVE_H

# include "save.h"
# include "structures.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

void	save_img(t_game *game, char *filename);
#endif
