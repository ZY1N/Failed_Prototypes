/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:04:20 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/25 11:40:33 by yinzhang         ###   ########.fr       */
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
	if(ft_strchr("#-+ .*0123456789hljz", format[position]) && !ft_strchr("cspdiouxXf%", format[position]))
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
	write(1, "You are using it wrong, re-read readme!", 39);
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
			while(ft_strchr("cspdiouxXf%#-+ .*0123456789hljz", format[position + 1]))
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

int     main()
{
	char c;

	c = 'D';
	
	printf("%9.2p\n\n", 1234);
	ft_printf("%9.2p", 1234);

}


/*Edge case: if string is NULL it shuld return null and work with percision*/
