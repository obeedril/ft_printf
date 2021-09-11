#include "ft_printf.h"

static void	zero(t_list *flag)
{
	flag->minus = 0;
	flag->zero = 0;
	flag->width = 0;
	flag->precision = -1;
	flag->percent = 0;
	flag->Ox = 0;
	flag->i = 0;
}

static void	identificators(t_list *flag, va_list args, const char **str)
{
	check_flags(flag, str, &*args);
	const char	*tmp;

	tmp = *str;
	if (*tmp == 'c')
		ft_symbol(&*flag, &*args);
	if (*tmp == '%')
		ft_percent(&*flag);
	if (*tmp == 's')
		ft_row(&*flag, &*args);
	if (*tmp == 'd' || *tmp == 'i')
		ft_digit(&*flag, &*args);
	if (*tmp == 'u')
		ft_udigit(&*flag, &*args);
	if (*tmp == 'X' || *tmp == 'x')
		ft_xdigit(&*flag, &*args, *str);
	if (*tmp == 'p')
		ft_pointer(&*flag, &*args, *str);
	tmp++;
	*str = tmp;
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_list	flag;

	zero(&flag);
	flag.len = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str != '%')
			{
				// check_flags(&flag, &str, &*args);
				identificators(&flag, &*args, &str);
				zero(&flag);
			}
			else if (*str == '%')
				flag.len += write(1, &*str++, 1);
		}
		if (*str != '%' && *str != '\0')
			flag.len += write(1, &*str++, 1);
	}
	va_end(args);
	return (flag.len);
}
