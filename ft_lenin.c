#include "ft_printf.h"

int	ft_lenin(t_list *flag, long res, int base)
{
	int		len_int;
	long	tmp;

	tmp = res;
	if (res == 0 && flag->precision != 0)
		return (1);
	len_int = 0;
	while (tmp)
	{
		len_int++;
		tmp = tmp / base;
	}
	return (len_int);
}
