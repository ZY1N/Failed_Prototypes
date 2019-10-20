#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

void print_ints(int num, ...)
{
	va_list args;

	va_start(args, num);
	
	for (int i=0; i < num; i++)
	{
		int value = va_arg(args, int);
		printf("%d: %d\n", i, value);
	}
	va_end(args);
}	



void ftputchar(char c)
{
	write(1, &c, 1);
}

void ftputstr(char *s)
{
	while (*s)
	{
		ftputchar(*s);
		s++;
	}
}

//int ftprintf(char *s)
//{
//	ftputstr(s);
//	return 0;
//}

int		ft_printf(char *string, ...)
{
	va_list args;
	va_start(args, )

}



int main()
{
	print_ints(3, 24, 25, 6546);
}
