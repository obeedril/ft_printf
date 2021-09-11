#include "ft_printf.h"

void	ft_putnbr_fd(t_list *flag, long int n, int fd)
{
	char	c;

	if (n < 0)
	{
		n = -n;
		ft_putnbr_fd(flag, n, fd);
	}
	else if (n < 10)
	{
		c = n + '0';
		flag->len += write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(flag, n / 10, fd);
		c = (n % 10) + '0';
		flag->len += write(fd, &c, 1);
	}
}
