/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:23:24 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:28:31 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int	strstarts(const char *str, const char *beg)
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

int	strends(const char *str, const char *end)
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

int	isin(char c, char *str)
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

int	ft_atoi(char **str)
{
	int	result;

	result = 0;
	if (str && *str)
	{
		while (**str == ' ' && **str != '\0')
			(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			result = result * 10 + **str - '0';
			(*str)++;
		}
	}
	return (result);
}
