#include "ft_printf.h"

static t_list	*give_flags(t_list *flag, int digit)
{
	if (flag->width < 0)
	{
		flag->minus = 1;
		flag->width = -flag->width;
		flag->zero = 0;
	}
	if (flag->precision < -1)
		flag->precision = -1;
	if (digit < 0)
	{
		flag->znak = 1;
		digit = -digit;
	}
	else if (digit >= 0)
		flag->znak = 0;
	return (flag);
}

static void	no_prec(int lenin, t_list *flag, int digit)
{
	flag->width = flag->width - lenin - flag->znak;
	if (flag->width < 0)
		flag->width = 0;
	if (flag->minus == 0)
	{
		if (flag->zero == 0)
			print_width(flag);
		if (flag->znak == 1)
			flag->len += write (1, "-", 1);
		if (flag->zero > 0)
			print_width(flag);
		ft_putnbr_fd(flag, digit, 1);
	}
	if (flag->minus == 1)
	{
		if (flag->znak == 1)
			flag->len += write (1, "-", 1);
		ft_putnbr_fd(flag, digit, 1);
		print_width(flag);
	}
}

static void	zero_prec(int lenin, t_list *flag, int digit)
{
	flag->width = flag->width - lenin - flag->znak;
	if (flag->width < 0)
		flag->width = 0;
	if (flag->minus == 0)
		print_width(flag);
	if (digit != 0)
	{
		if (flag->znak == 1)
			flag->len += write (1, "-", 1);
		ft_putnbr_fd(flag, digit, 1);
	}
	if (flag->minus == 1)
		print_width(flag);
	if (flag->width > 0 && digit == 0)
		print_width(flag);
	if (flag->width == 0 && digit == 0)
		return ;
}

static void	more_prec(int lenin, t_list *flag, int digit)
{
	if (flag->precision >= flag->width)
	{
		flag->minus = 0;
		flag->precision = flag->precision - lenin;
		if (flag->precision < 0)
			flag->precision = 0;
		flag->width = 0;
		if (flag->znak == 1)
			flag->len += write (1, "-", 1);
		print_precision(flag);
		ft_putnbr_fd(flag, digit, 1);
	}
	else if (flag->precision < flag->width)
	{
		flag = ft_gfd(flag, lenin);
		if (flag->minus == 0)
			print_width(flag);
		if (flag->znak == 1)
			flag->len += write (1, "-", 1);
		print_precision(flag);
		ft_putnbr_fd(flag, digit, 1);
		if (flag->minus == 1)
			print_width(flag);
	}
}

int	ft_digit(t_list *flag, va_list args)
{
	int	lenin;
	int	digit;

	digit = va_arg(args, int);
	lenin = ft_lenin(flag, digit, 10);
	flag = give_flags(flag, digit);
	if (flag->precision == -1)
		no_prec(lenin, flag, digit);
	if (flag->precision == 0)
		zero_prec(lenin, flag, digit);
	if (flag->precision > 0)
		more_prec(lenin, flag, digit);
	return (flag->len);
}
