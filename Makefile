NAME  = libftprintf.a

SRC	= 	ft_printf.c ft_lenin.c ft_putnbr_fd.c \
		ft_putudigit_fd.c ft_putxd.c check_flags.c\
		ft_symbol.c ft_percent.c ft_lenptr.c \
		ft_row.c ft_digit.c ft_udigit.c ft_xdigit.c \
		ft_pointer.c ft_atoi_width.c ft_gfd.c\
		 print_width_bonus.c print_precision_bonus.c \

BONUS_FILES	=	print_precision_bonus.c print_width_bonus.c	\

OBJ_BONUS	=	${BONUS_FILES:.c=.o}

OBJ			= ${SRC:.c=.o}

HEADER		= ft_printf.h

CC			= gcc

FLAGS		= -Wall -Wextra -Werror

RM			= rm -f

.c.o:		ft_printf.h
			${CC} ${FLAGS} -c $< -I ${HEADER} -o ${<:.c=.o}

${NAME}: 	${OBJ}
				ar rcs ${NAME} ${OBJ}

all: ${NAME}

clean:
	${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

rebonus:	fclean bonus

bonus:		all ${OBJ_BONUS}
					ar rcs ${NAME} ${OBJ_BONUS}

.PHONY: all clean fclean re bonus
