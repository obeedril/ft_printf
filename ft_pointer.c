#include "ft_printf.h"

static t_list	*get_flags_w(t_list *flag)
{
	if (flag->width < 0)
	{
		flag->minus = 1;
		flag->width = -flag->width;
		flag->zero = 0;
	}
	if (flag->precision < -1)
		flag->precision = -1;
	return (flag);
}

static void	no_zero_prec(int lenin, t_list *flag)
{
	flag->width = flag->width - lenin - flag->Ox;
	if (flag->width < 0)
		flag->width = 0;
	if (flag->minus == 0)
		print_width(flag);
	if (flag->Ox == 2)
		flag->len += write(1, "0x", 2);
}

static void	no_min(t_list *flag)
{
	if (flag->minus == 0)
		print_width(flag);
	if (flag->Ox == 2)
		flag->len += write(1, "0x", 2);
	print_precision(flag);
}

static t_list	*get_flags(t_list *flag, int lenin)
{
	if (flag->precision >= flag->width)
	{
		flag->minus = 0;
		flag->precision = flag->precision - lenin - flag->Ox;
		if (flag->precision < 0)
			flag->precision = 0;
		flag->width = 0;
	}
	else if (flag->precision < flag->width)
	{
		if (flag->width <= lenin)
			flag->width = 0;
		if (flag->precision > lenin)
		{
			flag->width = flag->width - flag->precision;
			flag->precision = flag->precision - lenin - flag->Ox;
		}
		else if (flag->precision <= lenin)
		{
			flag->precision = 0;
			flag->width = flag->width - lenin - flag->Ox;
		}
	}
	return (flag);
}

int	ft_pointer(t_list *flag, va_list args, const char *str2)
{
	int				lenin;
	unsigned long	ptr;

	ptr = 0;
	ptr = va_arg(args, unsigned long);
	lenin = ft_lenptr(flag, ptr, 16);
	flag = get_flags_w(flag);
	if (flag->precision == -1 || flag->precision == 0)
	{
		no_zero_prec(lenin, flag);
		if (flag->precision == -1 || (flag->precision == 0 && ptr != 0))
			ft_putxd(flag, ptr, 1, str2);
		if (flag->minus == 1)
			print_width(flag);
	}
	if (flag->precision > 0)
	{
		flag = get_flags(flag, lenin);
		no_min(flag);
		ft_putxd(flag, ptr, 1, str2);
		if (flag->minus == 1)
			print_width(flag);
	}
	return (flag->len);
}
