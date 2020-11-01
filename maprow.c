/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maprow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:13:46 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:40:13 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maprow.h"
#include "tools.h"

int			borderokay(char *str)
{
	char *end;

	end = str;
	while (*str == ' ')
		str++;
	if (*str != '1')
		return (0);
	while (*end)
		end++;
	end--;
	while (end >= str && *str == ' ')
		end--;
	if (*end != '1')
		return (0);
	return (1);
}

t_map_row	*new_row(char *str)
{
	t_map_row	*new;

	new = NULL;
	if (str)
	{
		new = malloc(sizeof(t_map_row));
		if (new)
		{
			new->line = ft_strdup(str);
			new->len = ft_strlen(str);
			new->next = NULL;
		}
	}
	return (new);
}

int			append_row(t_map_row **head, int *maxwidth, char *str)
{
	int			rc;
	t_map_row	*new;
	t_map_row	*cur;

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
	else if (*head)
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
		if (*maxwidth < new->len)
			*maxwidth = new->len;
	}
	return (rc);
}

void		free_map(t_map_row **head)
{
	t_map_row	*tmp;

	if (head)
	{
		while (*head)
		{
			free((*head)->line);
			tmp = (*head)->next;
			free(*head);
			*head = tmp;
		}
	}
}
