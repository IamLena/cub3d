/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalecto <nalecto@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:47:38 by nalecto           #+#    #+#             */
/*   Updated: 2020/09/07 19:29:42 by nalecto          ###   ########.fr       */
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
		while(str[n] != '\0')
			n++;
	return (n);
}

int			strstarts(const char *str, const char *beg)
{
	if (str && beg)
	{
		while(*beg != '\0')
		{
			if (*beg != *str)
				return 0;
			beg++;
			str++;
		}
		return 1;
	}
	return 0;
}

int			strends(const char *str, const char *end)
{
	int strlen;
	int endlen;
	if (str && end)
	{
		strlen = ft_strlen(str);
		endlen = ft_strlen(end);
		if (strlen > endlen)
		{
			str += strlen - endlen;
			while(*end != '\0')
			{
				if (*end != *str)
					return 0;
				end++;
				str++;
			}
			return 1;
		}
	}
	return 0;
}

int			isin(char c, char *str)
{
	if (str)
	{
		while(*str != '\0')
		{
			if (*str == c)
				return (1);
			str++;
		}
	}
	return (0);
}

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

int			ft_atoi(char **str)
{
	int result = 0;
	if (str && *str)
	{
		while (**str == ' ' && **str != '\0')
			(*str)++;
		while(**str >= '0' && **str <= '9')
		{
			result = result * 10 + **str - '0';
			(*str)++;
		}
	}
	return (result);
}

int			comma_error(char **str)
{
	if (str && *str)
	{
		while (**str == ' ' && **str != '\0')
			(*str)++;
		if (**str == ',')
		{
			(*str)++;
			return (0);
		}
	}
	return (1);
}

void		print_matrix(char **matrix)
{
	int i = 0;
	int j = 0;

	if (matrix)
	{
		while (matrix[i])
		{
			j = 0;
			while(matrix[i][j])
			{
				write(1, &matrix[i][j], 1);
				j++;
			}
			write(1, "|\n", 2);
			i++;
		}
	}
}

void		free_matrix(char **matrix, int row_index)
{
	int i = 0;
	if (matrix)
	{
		while (matrix[i] && i < row_index)
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}
