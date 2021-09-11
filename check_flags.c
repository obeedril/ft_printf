#include "ft_printf.h"

static char	find_iden(const char *str2)
{
	char	iden;

	iden = 0;
	if ((*str2 == 'c' || *str2 == 's' || *str2 == 'd' || *str2 == 'i'
			|| *str2 == 'u' || *str2 == 'x' || *str2 == 'X' || *str2 == 'p'
			|| *str2 == '%') && *str2 != '\0')
		iden = *str2;
	return (iden);
}

static t_list	*get_flags_w(t_list *flag, const char **str2, va_list args)
{
	const char	*tmp;

	tmp = *str2;
	if (*tmp == '*')
	{
		flag->width = va_arg(args, int);
		tmp++;
	}
	if (*tmp >= '0' && *tmp <= '9')
	{
		flag->width = ft_atoi_width(&*tmp);
		flag->i = ft_lenin(flag, flag->width, 10);
		tmp = tmp + (flag->i - 1);
		tmp++;
	}
	*str2 = tmp;
	return (flag);
}

static t_list	*get_flags_pr(t_list *flag, const char *str2, va_list args)
{
	if (*str2 == '*')
		flag->precision = va_arg(args, int);
	else if (*str2 >= '0' && *str2 <= '9')
	{
		flag->precision = ft_atoi_width(&*str2);
		flag->i = ft_lenin(flag, flag->precision, 10);
	}
	else
		flag->precision = 0;
	return (flag);
}

static t_list	*get_flags_zm(t_list *flag, const char *str2)
{
	if (*str2 == '-')
		flag->minus = 1;
	if (*str2 == '0')
		flag->zero = 1;
	if (flag->minus == 1 && flag->zero == 1)
		flag->zero = 0;
	return (flag);
}

void	check_flags(t_list *flag, const char **str, va_list args)
{
	const char	*str2;

	str2 = *str;
	while (*str2 == '-' || *str2 == '0')
	{
		flag = get_flags_zm(flag, str2);
		str2++;
	}
	flag = get_flags_w(flag, &str2, args);
	if (*str2 == '.')
	{
		str2++;
		flag = get_flags_pr(flag, str2, args);
	}
	while (!find_iden(str2))
		str2++;
	if (*str2 == 'p')
		flag->Ox = 2;
	if (*str2 == '%')
		flag->percent = '%';
	*str = str2;
}
