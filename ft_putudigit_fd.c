#include "ft_printf.h"

void	ft_putudigit_fd(t_list *flag, unsigned int n, int fd)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		flag->len += write(fd, &c, 1);
	}
	else if (n >= 10)
	{
		ft_putudigit_fd(flag, n / 10, fd);
		c = (n % 10) + '0';
		flag->len += write(fd, &c, 1);
	}
}
