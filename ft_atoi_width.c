#include "ft_printf.h"

int	ft_atoi_width(const char *str2)
{
	int	res;

	res = 0;
	while (*str2 >= 48 && *str2 <= 57)
	{
		if (res > INT_MAX / 10)
			return (-1);
		else
		{
			res = res * 10 + (*str2 - 48);
			str2++;
		}
	}
	return (res);
}
