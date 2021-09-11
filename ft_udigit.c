#include "ft_printf.h"

static void	no_zero_prec(int lenin, t_list *flag, int udigit)
{
	flag->width = flag->width - lenin;
	if (flag->width < 0)
		flag->width = 0;
	if (flag->minus == 0)
		print_width(flag);
	if (flag->precision == -1 || (flag->precision == 0 && udigit != 0))
		ft_putudigit_fd(flag, udigit, 1);
	if (flag->minus == 1)
		print_width(flag);
}

static t_list	*get_flag_w(t_list *flag)
{
	flag->minus = 1;
	flag->width = -flag->width;
	flag->zero = 0;
	return (flag);
}

static t_list	*get_flags(t_list *flag, int lenin)
{
	if (flag->precision >= flag->width)
	{
		flag->minus = 0;
		flag->precision = flag->precision - lenin;
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
			flag->precision = flag->precision - lenin;
		}
		else if (flag->precision <= lenin)
		{
			flag->precision = 0;
			flag->width = flag->width - lenin ;
		}
	}
	return (flag);
}

int	ft_udigit(t_list *flag, va_list args)
{
	int				lenin;
	unsigned int	udigit;

	udigit = va_arg(args, unsigned int);
	if (flag->width < 0)
		flag = get_flag_w(flag);
	lenin = ft_lenin(flag, udigit, 10);
	if (flag->precision < -1)
		flag->precision = -1;
	if (flag->precision == -1 || flag->precision == 0)
		no_zero_prec(lenin, flag, udigit);
	if (flag->precision > 0)
	{
		flag = get_flags(flag, lenin);
		if (flag->minus == 0)
			print_width(flag);
		print_precision(flag);
		ft_putudigit_fd(flag, udigit, 1);
		if (flag->minus == 1)
			print_width(flag);
	}
	return (flag->len);
}
