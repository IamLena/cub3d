#ifndef TOOLS_H
# define TOOLS_H
# define BUFFER_SIZE 32

#include <unistd.h>
#include <stdlib.h>

void	errorexit(int rc, char *msg, char free_msg_flag);
int     ft_strlen(const char *str);
char    *ft_strdup(const char *str);
int     get_next_line(int fd, char **line);
int     strstarts(const char *str, const char *beg);
int     strends(const char *str, const char *end);
int     isin(char c, char *str);
int     ft_atoi(char **str);
int     comma_error(char **str);
void    print_matrix(char **matrix);
void    free_matrix(char **matrix, int row_index);

#endif
