#include "ft_printf.h"

void	ft_putxd(t_list *flag, unsigned long n, int fd, const char *str2)
{
	unsigned long	digit_count;
	unsigned long	tmp;
	char			*base;

	if (*str2 == 'X')
		 base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	digit_count = 1;
	tmp = n;
	while (tmp)
	{
		tmp /= 16;
		if (!(tmp))
			break ;
		digit_count *= 16;
	}
	while (digit_count)
	{
		flag->len += write (fd, &base[(n / digit_count)], 1);
		n %= digit_count;
		digit_count /= 16;
	}
}
