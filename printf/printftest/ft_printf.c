/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:04:20 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/29 17:17:12 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

void	bezerostruct(t_struct *list)
{
	list->i = 0;
	list->nprinted = 0;
	list->len = 0;
	list->minus = 0;
	list->plus = 0;
	list->space = 0;
	list->zero = 0;
	list->hash = 0;
	list->width = 0;
	list->precisionTF = 0;
	list->precision = 0;
	list->length = 0;
}

void	bezerostruct2(t_struct *list)
{
	list->len = 0;
	list->minus = 0;
	list->plus = 0;
	list->space = 0;
	list->zero = 0;
	list->hash = 0;
	list->width = 0;
	list->precisionTF = 0;
	list->precision = 0;
	list->length = 0;
}

int		parsel2(t_struct *f, int position, const char *format, va_list ap)
{
	f->i = position;
	if(ft_strchr("#-+ .*0123456789hlLjz", format[position]) && !ft_strchr("cspdiouxXf%", format[position]))
		modifiers(format, f, ap);
	else if(ft_strchr(("cspdiouxXf%"), format[position]))
	{
		conversions(format[position], position, ap, f);
		bezerostruct2(f);
	}
	return(f->i - 1);
}


void error()
{
	write(1, "", 0);
}

int		formatparse(const char *format, t_struct *list, va_list ap)
{
	int position;

	position = 0;
	if (!format[0])
	{
		error();
		return 0;
	}
	while(format[position])
	{
		if(format[position] != '%')
		{
			write(1, &format[position], 1);
			list->nprinted++;
		}
		else if(format[position] == '%')
		{
			while(ft_strchr("cspdiouxXf%#-+ .*0123456789hLljz", format[position + 1]))
			{
				position = position + 1;
				if(ft_strchr("cspdiouxXf%", format[position]))
				{
					position = parsel2(list, position, format, ap);
					position = position + 2;
					break;
				}
				else
					position = parsel2(list, position, format, ap);
			}
			continue;
		}
		position++;
	}
	return (list->nprinted);
}

int     ft_printf(const char *format, ...)
{
    va_list ap;
    int status;
    t_struct *s;

    if (!(s = (t_struct*)malloc(sizeof(t_struct))))
        return(0);
    bezerostruct(s);
    s->format = (char *)format;
    va_start(ap, format);
    status = formatparse(format, s, ap);
    va_end(ap);
    free(s);
    return(status);
}

/*
int     main()
{
	static unsigned int		mx_u = 235;
static long double			mx_Lf = 0.375l;
static double				mx_f = 0.625;
static long				mx_li =  4223372036854775800;
static long long			mx_lli = 3223372036654775200;
static char				mx_c = 'G';
static short				mx_hi = -3244;
static char				mx_hhi = 'F';
static char			   *mx_s = "Hello, World!";
static int					mx_i = 42;
		
	
	ft_printf("[%x    %s    %i    %p    %X][%Lf] 66566  \n",
			mx_u, mx_s, mx_i, &mx_i, mx_u, mx_Lf);

} */

/*
int main()
{
	ft_printf("ft: [% 05.0f]\n", 7.3);
	printf("OG: [% 05.0f]\n", 7.3);
//	printf("og: this %#.0f float\n", 1.6);
}*/