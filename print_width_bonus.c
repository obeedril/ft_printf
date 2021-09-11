#include "ft_printf.h"

int	print_width(t_list *flag)
{
	char	c;

	while (flag->width > 0)
	{
		if (flag->zero == 0)
			c = ' ';
		else if (flag->zero == 1 && (flag->precision == -1 || flag->percent))
			c = '0';
		else if (flag->zero == 1 && flag->precision > -1)
			c = ' ';
		flag->len += write (1, &c, 1);
		flag->width--;
	}
	return (0);
}
