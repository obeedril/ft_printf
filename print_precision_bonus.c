#include "ft_printf.h"

int	print_precision(t_list *flag)
{
	while (flag->precision > 0)
	{
		flag->len += write (1, "0", 1);
		flag->precision--;
	}
	return (0);
}
