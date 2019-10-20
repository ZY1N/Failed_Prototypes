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

char	*ft_itoa_base_upper(uintmax_t value, uintmax_t base)
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
		s[i] = (n % base < 10) ? n % base + '0' : n % base + 'A' - 10;
		n /= base;
	}
	(i == 0) ? s[i] = '-' : 0;
	return (s);
}


/*
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
*/



void    right_aligned_hex(t_struct *f, int widthp, int precisionp, int hexlenp, char *s, char c, int hash, char x)
{
    /*special case where you need a zero after OX*/
    if (c == '0' && hash == 2)
    {
        if (hash == 2 && x == 'x')
            f->nprinted += write(1, "0x", 2);
        else if (hash == 2 && x == 'X')
            f->nprinted += write(1, "0X", 2);
        while(widthp > 0)
        {
            f->nprinted += write(1, &c, 1);
            widthp--;
	    }
        while (precisionp > 0)
	    {
	    	f->nprinted += write(1, "0", 1);
	    	precisionp--;	
        }
	    f->nprinted += write(1, s, hexlenp);
        return ;
    }

    while(widthp > 0)
	{
		f->nprinted += write(1, &c, 1);
		widthp--;
	}
    if (hash == 2 && x == 'x')
        f->nprinted += write(1, "0x", 2);
    else if (hash == 2 && x == 'X')
        f->nprinted += write(1, "0X", 2);
	while (precisionp > 0)
	{
		f->nprinted += write(1, "0", 1);
		precisionp--;	
    }
	f->nprinted += write(1, s, hexlenp);
}


void	left_aligned_hex(t_struct *f, int widthp, int precisionp, int hexlenp, char *s, int hash, char x)
{
    if (hash == 2 && x == 'x')
        f->nprinted += write(1, "0x", 2);
    else if (hash == 2 && x == 'X')
        f->nprinted += write(1, "0X", 2);
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

void    formatextractionhex(uintmax_t n, t_struct *f, char x)
{
    int hashp;
    int precisionp;
    int octlenp;
    int widthp;
    char *s;
    char c;

    if(f->zero && !f->precisionTF)
        c = '0';
    else
        c = ' ';
    if (x == 'x')
        s = ft_itoa_base(n, 16);
    else if (x == 'X')
        s = ft_itoa_base_upper(n, 16); 
    hashp = 0;
    octlenp = unsigned_nbr_len(n, 16);
    if (f->hash)
        hashp = 2;
   // printf("\n\noctlenp before: %d\n\n", octlenp);
     if (n == 0)
    {
        octlenp = 1;
        if (hashp == 2)
            hashp = 0;
        if (f->precisionTF && f->precision == 0)
            octlenp = 0;
    }    
  //  printf("\n\noctlenp after: %d\n\n", octlenp);
  //  printf("\n\nnumber int %ju\n\n", n);
    if(f->precisionTF && f->precision > octlenp)
        precisionp = f->precision - octlenp /*- hashp*/;
    else
        precisionp = 0;
    widthp = f->width - (precisionp + octlenp) - hashp;
  //  printf("\n\nwidthp: %d precisionp: %d octlenp: %d hashp: %d\n\n", widthp, precisionp, octlenp, hashp);
  // printf("\n\n\n\nstring %s\n\n", s);
    if (f->minus == 0)
        right_aligned_hex(f, widthp, precisionp, octlenp, s, c, hashp, x);
    else if (f->minus == 1)
        left_aligned_hex(f, widthp, precisionp, octlenp, s, hashp, x);
}

void ifhex(t_struct *f, va_list ap, char x)
{
    uintmax_t n;

    n = 0;
    if (f->length == 0)
        n = (unsigned int)va_arg(ap, unsigned int);
    else if (f->length == HH)
        n = (unsigned char)va_arg(ap, int);
    else if (f->length == H)
        n = (unsigned short)va_arg(ap, int);
    else if (f->length == LL)
        n = (unsigned long long int)va_arg(ap, uintmax_t);
    else if (f->length == L)
        n = (unsigned long int)va_arg(ap, uintmax_t);
    
    formatextractionhex(n, f, x);
}


