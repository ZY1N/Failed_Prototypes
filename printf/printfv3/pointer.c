/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:45:33 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/24 19:46:42 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		hex_count(unsigned long long n)
{
	int i;

	i = 0;
	while (n / 16)
	{
		n = n / 16;
		i++;
	}
	return(i);
}	

char	*ft_itoa_base(unsigned long long value, int base)
{
	char				*s;
	unsigned long long	n;
	int					sign;
	int					i;

	n = (value < 0) ? -(long)value : value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		i++;
	s = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	n = (value < 0) ? -(long)value : value;
	while (i-- + sign)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base + 'a' - 10;
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}


//if there is a minus sign
void	leftaligned(unsigned long long pointer, t_struct *f)
{
	int i;
	char *s;

	s = ft_itoa_base(pointer, 16);
	i = hex_count(pointer) + 1;
	if(f->precisionTF && i > f->precision)
		i = f->precision + 1;
	f->nprinted = f->nprinted + write(1, "0x", 2);
	f->nprinted = f->nprinted + write(1, s, i);
	while(f->width - 2 > i)
	{
		write(1, " ", 1);
		f->nprinted++;
		f->width--;
	}
}

//if there isnt a minus sign
void	rightaligned(unsigned long long pointer, t_struct *f)
{
	int i;
	char *s;

	s = ft_itoa_base(pointer, 16);
	i = hex_count(pointer) + 1;
	if(f->precisionTF && i > f->precision)
		i = f->precision + 1;
	while(f->width - i - 2 > 0)
	{
		f->len = f->len + write(1, " ", 1);
		f->nprinted++;
		f->width--;
	}
	f->nprinted = f->nprinted + write(1, "0x", 2);
	f->nprinted = f->nprinted + write(1, s, i);
}

void	ifpointer(t_struct *f, va_list ap)
{
 	unsigned long long pointer;

    pointer = (unsigned long long)va_arg(ap, void *);
	if(f->minus)
		leftaligned(pointer, f);
	else
		rightaligned(pointer, f);
}