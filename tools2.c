/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:18:48 by nalecto           #+#    #+#             */
/*   Updated: 2020/11/01 01:28:19 by nalecto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char		*ft_strdup(const char *str)
{
	int		len;
	char	*cp;
	int		i;

	len = ft_strlen(str);
	cp = malloc(len + 1);
	if (cp)
	{
		i = 0;
		while (i < len)
		{
			cp[i] = str[i];
			i++;
		}
		cp[i] = '\0';
	}
	return (cp);
}

static int	findnpos(const char *str)
{
	int pos;

	pos = 0;
	while (str[pos] != '\n' && str[pos] != '\0')
		pos++;
	return (pos);
}

static int	ft_join(char **line, char *buf, int linelen, int npos)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	tmp = malloc(linelen + npos + 1);
	if (tmp)
	{
		j = 0;
		while (i < linelen)
		{
			tmp[i] = (*line)[i];
			i++;
		}
		while (j < npos)
			tmp[i++] = buf[j++];
		tmp[i] = '\0';
		if (*line != NULL)
			free(*line);
		*line = tmp;
		tmp = NULL;
	}
	return (j);
}

static char	*appendline(char **line, char *buf, int buflen)
{
	int		linelen;
	int		npos;
	char	*next;
	int		j;

	linelen = ft_strlen(*line);
	npos = findnpos(buf);
	next = NULL;
	j = ft_join(line, buf, linelen, npos);
	if (j != -1 && npos != buflen)
		next = ft_strdup(&(buf[j + 1]));
	return (next);
}

int			get_next_line(int fd, char **line)
{
	char		*buf;
	int			ret;
	static char	*next;
	char		*tmp;

	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strdup("");
	if (next)
	{
		tmp = appendline(line, next, ft_strlen(next));
		free(next);
		if ((next = tmp) != NULL)
			return (1);
	}
	if ((buf = malloc(BUFFER_SIZE + 1)) == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((next = appendline(line, buf, ret)) != NULL)
			break ;
	}
	free(buf);
	return (ret > 0 ? 1 : ret);
}
