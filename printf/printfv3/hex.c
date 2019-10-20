/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 15:28:49 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/27 15:28:52 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base_upper(unsigned long long value, int base)
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
		s[i] = (n % base < 10) ? n % base + '0' : n % base + 'A' - 10;
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}

void    paddinghex(int nbrlen, int difference, t_struct *f, char c)
{
    while (f->width-- > nbrlen + difference)
        f->nprinted += write(1, &c, 1);
}

void    print0x(t_struct *f, char c)
{
    if(c == 'x')
        f->nprinted += write(1, "0x", 2);
    else if(c == 'X')
        f->nprinted += write(1, "0X", 2);
}

void    printhexupperlower(int n, t_struct *f, char x, int nbrlen)
{
    char *s;

    if (x == 'x')
    {
        s = ft_itoa_base(n, 16);
        f->nprinted += write(1, s, nbrlen);
    }
    else if (x == 'X')
    {
        s = ft_itoa_base_upper(n, 16);
        f->nprinted += write(1, s, nbrlen);
    }
}

void    right_aligned_hex(uintmax_t n, t_struct *f, char x)
{
    int nbrlen;
    char c;
    int difference;

    difference = 0;
    nbrlen = unsigned_nbr_len(n, 16);

    if (f->zero == 1)
        c = '0';
    else
        c = ' ';
    if (f->precisionTF && f->precision > nbrlen)
        difference = f->precision - nbrlen;
    if (f->hash == 1)
        f->width = f->width - 2;
    paddinghex(nbrlen, difference, f, c);
    if (n != 0 && f->hash == 1)
          print0x(f, x);
    while(difference > 0)
    {
        f->nprinted += write(1, "0", 1);
        difference--;
    }
    printhexupperlower(n, f, x, nbrlen);
}

void    left_aligned_hex(uintmax_t n, t_struct *f, char x)
{
    int nbrlen;
    char c;
    int difference;

    difference = 0;
    nbrlen = unsigned_nbr_len(n, 16);
    
    c = ' ';
    if (f->precisionTF && f->precision > nbrlen)
        difference = f->precision - nbrlen;
    if (f->hash == 1)
        f->width -= 2;
    if (f->hash == 1 && n != 0)
        print0x(f, x);
    while(difference > 0)
    {
        f->nprinted += write(1, "0", 1);
        difference--;
    }
    printhexupperlower(n, f, x, nbrlen);
    paddinghex(nbrlen, difference, f, c);
}

void ifhex(t_struct *f, va_list ap, char x)
{
    uintmax_t n;

    if (f->length == 0)
        n = va_arg(ap, unsigned int);
    else if (f->length == HH)
        n = (unsigned char)va_arg(ap, unsigned int);
    else if (f->length == H)
        n = (unsigned short)va_arg(ap, unsigned int);
    else if (f->length == LL)
        n = (unsigned long long)va_arg(ap, unsigned long long);
    else if (f->length == L)
        n = (unsigned long)va_arg(ap, unsigned long);
    if (f->minus == 0)
        right_aligned_hex(n, f, x);
    else if (f->minus == 1)
        left_aligned_hex(n, f, x);
}