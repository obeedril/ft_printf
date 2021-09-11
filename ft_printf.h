#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list{
	int	minus;
	int	zero;
	int	width;
	int	precision;
	int	i;
	int	znak;
	int	len;
	int	Ox;
	int	percent;
}	t_list;

int		ft_printf(const char *str, ...);
int		ft_lenin(t_list *flag, long res, int base);
void	ft_putnbr_fd(t_list *flag, long int n, int fd);
void	ft_putudigit_fd(t_list *flag, unsigned int n, int fd);
void	ft_putxd(t_list *flag, unsigned long int n, int fd, const char *str2);
int		print_width(t_list *flag);
int		print_precision(t_list *flag);
int		ft_symbol(t_list *flag, va_list args);
int		ft_percent(t_list *flag);
int		ft_row(t_list *flag, va_list args);
int		ft_digit(t_list *flag, va_list args);
int		ft_udigit(t_list *flag, va_list args);
int		ft_xdigit(t_list *flag, va_list args, const char *str2);
int		ft_pointer(t_list *flag, va_list args, const char *str2);
int		ft_atoi_width(const char *str2);
void	check_flags(t_list *flag, const char **str, va_list args);
int		ft_lenptr(t_list *flag, unsigned long res, int base);
t_list	*ft_gfd(t_list *flag, int lenin);

#endif