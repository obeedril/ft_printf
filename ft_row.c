#include "ft_printf.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}

static t_list	*get_w(t_list *flag)
{
	if (flag->width < 0)
	{
		flag->minus = 1;
		flag->width = -flag->width;
		flag->zero = 0;
	}
	return (flag);
}

static void	no_prec(t_list *flag, char *row, int row_len)
{
	flag->width = flag->width - row_len;
	if (flag->width < 0)
		flag->width = 0;
	if (flag->minus == 0)
		print_width(flag);
	flag->len += write (1, row, row_len);
	if (flag->minus == 1)
		print_width(flag);
}

static void	more_prec(t_list *flag, char *row, int row_len)
{
	if (row_len < flag->precision)
	{
		flag->width = flag->width - row_len;
		flag->precision = row_len;
	}
	else
		flag->width = flag->width - flag->precision;
	if (flag->width < 0)
		flag->width = 0;
	if (flag->minus == 0)
		print_width(flag);
	flag->len += write (1, row, flag->precision);
	if (flag->minus == 1)
		print_width(flag);
}

int	ft_row(t_list *flag, va_list args)
{
	int		row_len;
	char	*row;

	row = NULL;
	row = va_arg(args, char *);
	if (!row)
		row = "(null)";
	row_len = ft_strlen(row);
	flag = get_w(flag);
	if (flag->precision < -1)
		flag->precision = row_len;
	if (flag->precision == -1)
		no_prec(flag, row, row_len);
	else if (flag->precision == 0)
		print_width(flag);
	if (flag->precision > 0)
		more_prec(flag, row, row_len);
	return (flag->len);
}
