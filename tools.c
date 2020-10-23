/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:47:38 by nalecto           #+#    #+#             */
/*   Updated: 2020/10/21 23:25:55 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void		errorexit(int rc, char *msg, char free_msg_flag)
{
	write(1, "Error\n", 6);
	write(1, msg, ft_strlen(msg));
	if (free_msg_flag)
		free(msg);
	exit(rc);
}

int			ft_strlen(const char *str)
{
	int	n;

	n = 0;
	if (str)
		while (str[n] != '\0')
			n++;
	return (n);
}

int			strstarts(const char *str, const char *beg)
{
	if (str && beg)
	{
		while (*beg != '\0')
		{
			if (*beg != *str)
				return (0);
			beg++;
			str++;
		}
		return (1);
	}
	return (0);
}

int			strends(const char *str, const char *end)
{
	int	strlen;
	int	endlen;

	if (str && end)
	{
		strlen = ft_strlen(str);
		endlen = ft_strlen(end);
		if (strlen > endlen)
		{
			str += strlen - endlen;
			while (*end != '\0')
			{
				if (*end != *str)
					return (0);
				end++;
				str++;
			}
			return (1);
		}
	}
	return (0);
}

int			isin(char c, char *str)
{
	if (str)
	{
		while (*str != '\0')
		{
			if (*str == c)
				return (1);
			str++;
		}
	}
	return (0);
}
