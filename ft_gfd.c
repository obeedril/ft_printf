#include "ft_printf.h"

t_list	*ft_gfd(t_list *flag, int lenin)
{
	if (flag->width <= lenin)
		flag->width = 0;
	if (flag->precision > lenin)
	{
		flag->width = flag->width - flag->precision - flag->znak;
		flag->precision = flag->precision - lenin;
	}
	else if (flag->precision <= lenin)
	{
		flag->precision = 0;
		flag->width = flag->width - lenin - flag->znak;
	}
	return (flag);
}
