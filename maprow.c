/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maprow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:13:46 by nalecto           #+#    #+#             */
/*   Updated: 2020/09/14 09:39:21 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maprow.h"

t_map_row *new_row(char *str)
{
    t_map_row *new;
    new = NULL;
    if (str)
    {
        new = malloc(sizeof(t_map_row));
        if (new) {
            new->line = ft_strdup(str);
            new->len = ft_strlen(str);
            new->next = NULL;
        }
    }
    return (new);

}

int append_row(t_map_row **head, int *maxwidth, char *str)
{
    int rc;
    t_map_row *new;
    t_map_row* cur;

    rc = 0;
    if (!head)
        rc = -1;
    else if (!(new = new_row(str)))
        rc = -1;
    else if (!(*head))
    {
        *head = new;
        *maxwidth = new->len;
    }
    else if (*head) {
        cur = *head;
        while (cur->next)
            cur = cur->next;
        cur->next = new;
        if (*maxwidth < new->len)
            *maxwidth = new->len;
    }
    return (rc);
}

void free_map(t_map_row **head) {
    t_map_row *tmp;
    if (head) {
        while (*head) {
            free((*head)->line);
            tmp = (*head)->next;
            free(*head);
            *head = tmp;
        }
    }
}

void print_map(t_map_row *head)
{
    while (head)
    {
        write(1, head->line, head->len);
        write(1, "\n", 1);
        head = head->next;
    }
}