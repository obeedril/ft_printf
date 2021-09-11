#include "ft_printf.h"

int	ft_symbol(t_list *flag, va_list args)
{
	int	symbol;

	symbol = va_arg(args, int);
	if (flag->width < 0)
	{
		flag->minus = 1;
		flag->width = -flag->width;
		flag->zero = 0;
	}
	if (flag->width > 0)
		flag->width--;
	if (flag->minus == 0)
		print_width(flag);
	flag->len += write(1, &symbol, 1);
	if (flag->minus == 1)
		print_width(flag);
	return (flag->len);
}
