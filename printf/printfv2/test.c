#include "ft_printf.h"

ft_printf(const char *format, ...);

int		main()
{
	char d;
	d = 'B';

	ft_printf("%4c\n", d);
	ft_printf("%-4c", d);
}
