/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maprow.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:12:33 by nalecto           #+#    #+#             */
/*   Updated: 2020/09/07 19:36:30 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPROW_H
#define MAPROW_H

#include <stdlib.h>
#include "maprow.h"
#include "tools.h"

typedef struct s_map_row
{
    char *line;
    int len;
    struct s_map_row *next;
} t_map_row;

t_map_row *new_row(char *str);
int append_row(t_map_row **head, int *maxwidth, char *str);
void free_map(t_map_row **head);
void print_map(t_map_row *head);

#endif