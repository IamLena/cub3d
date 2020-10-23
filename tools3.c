#include "tools.h"

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
