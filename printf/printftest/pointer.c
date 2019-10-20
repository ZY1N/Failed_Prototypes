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

char	*ft_itoa_base(uintmax_t value, uintmax_t base)
{
	char				*s;
	unsigned long long	n;
	int					sign;
	int					i;

	n = (value < 0) ? -value : value;
	sign = (value < 0 && base == 10) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while ((n /= base) >= 1)
		i++;
	s = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	n = (value < 0) ? -value : value;
	while (i-- + sign)
	{
		s[i] = (n % base < 10) ? n % base + '0' : n % base + 'a' - 10;
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}


/*
void	leftaligned(unsigned long long pointer, t_struct *f)
{
	int i;
	char *s;
	int lengthnoox;

	s = ft_itoa_base(pointer, 16);
	i = hex_count(pointer) + 1;
	lengthnoox = i;
	if (pointer == 0)
	{
		i = 1;
		lengthnoox = 1;
	}
	if(f->precisionTF && i < f->precision)
		i = f->precision;
	f->nprinted = f->nprinted + write(1, "0x", 2);
	writezeros(f->precision - lengthnoox);
	f->nprinted = f->nprinted + write(1, s, i);
	while(f->width - 2 > i)
	{
		write(1, " ", 1);
		f->nprinted++;
		f->width--;
	}
}


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

void	rightaligned(unsigned long long pointer, t_struct *f)
{
	int i;
	char *s;
	int lengthnoox;

	s = ft_itoa_base(pointer, 16);
	i = hex_count(pointer) + 1;
	lengthnoox = i;
	if(f->precisionTF && i < f->precision)
		i = f->precision;
	while(f->width - i - 2 > 0)
	{
		f->len = f->len + write(1, " ", 1);
		f->nprinted++;
		f->width--;
	}
	f->nprinted = f->nprinted + write(1, "0x", 2);
	writezeros(f->precision - lengthnoox);
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
}*/


void rightaligned(t_struct *f, int widthp, int precisionp, int hexlenp, char *s)
{
	while(widthp > 0)
	{
		f->nprinted += write(1, " ", 1);
		widthp--;
	}
	f->nprinted += write(1, "0x", 2);
	while (precisionp > 0)
	{
		f->nprinted += write(1, "0", 1);
		precisionp--;	
	}
	f->nprinted += write(1, s, hexlenp);
}

void	leftaligned(t_struct *f, int widthp, int precisionp, int hexlenp, char *s)
{
	f->nprinted += write(1, "0x", 2);
	while (precisionp > 0)
	{
		f->nprinted += write(1, "0", 1);
		precisionp--;	
	}
	f->nprinted += write(1, s, hexlenp);
	while(widthp > 0)
	{
		f->nprinted += write(1, " ", 1);
		widthp--;
	}
} 



void	ifpointer(t_struct *f, va_list ap)
{
 	unsigned long long pointer;
	int hexlenp;
	char *s;
	int precisionp;
	int widthp;
	int Oxheading;

	pointer = (unsigned long long)va_arg(ap, void *);

	Oxheading = 2;
	hexlenp = hex_count(pointer) + 1;
	s = ft_itoa_base(pointer, 16);
	precisionp = f->precision - hexlenp;
	widthp = f->width - hexlenp - Oxheading;
	if (f->precisionTF && f->precision == 0)
		hexlenp = 0;

	if(f->minus)
		leftaligned(f, widthp, precisionp, hexlenp, s);
	else
		rightaligned(f, widthp, precisionp, hexlenp, s);
}