/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:45:52 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/26 13:45:54 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    padding(int nbrlen, int difference, t_struct *f, char c)
{ 
    /*width is subtracted to make room for hashtag*/
    //if (f->hash)
    //    f->width--;
    while (f->width-- > nbrlen + difference)
        f->nprinted += write(1, &c, 1);
}

void    right_aligned_octal(uintmax_t n, t_struct *f)
{
    int nbrlen;
    char c;
    int difference;
    char *s;

    difference = 0;
    nbrlen = unsigned_nbr_len(n, 8);

    if (f->zero == 1)
        c = '0';
    else
        c = ' ';
    if (f->precisionTF && f->width)
        c = ' ';



    if (f->precisionTF && f->precision > nbrlen)
        difference = f->precision - nbrlen;
    /*this portion is to write the padding from the width*/
    if(f->hash && f->width && !f->precision)
        f->width--;
    padding(nbrlen, difference, f, c);
    /*this part is to write the hashtag, once it is written the difference should shrink by 1*/
    if (f->hash == 1 && n != 0)
    {
        f->nprinted += write(1, "0", 1);
        difference --;
    }
    while (difference > 0)
    {
        f->nprinted += write(1, "0", 1);
        difference--;
    }
    s = ft_itoa_base(n, 8);
    f->nprinted += write(1, s, nbrlen);
}

void    paddingleftaligned(int nbrlen, int differenceog, t_struct *f)
{
    while (f->width-- > nbrlen + differenceog)
        f->nprinted += write(1, " ", 1);
}

void    left_aligned_octal(uintmax_t n, t_struct *f)
{
    int nbrlen;
    char c;
    int difference;
    char *s;
    int differenceog;

    difference = 0;
    nbrlen = unsigned_nbr_len(n, 8);
    
    c = ' ';
    if (f->precisionTF && (f->precision > nbrlen))
        difference = f->precision - nbrlen;
    
    if (f->hash == 1 && n != 0)
    {
        f->nprinted += write(1, "0", 1);
        if (difference > 0)
            difference--;
        f->width--;
    }
    differenceog = difference;
    while(difference > 0)
    {
        f->nprinted += write(1, "0", 1);
        difference--;
    }
    s = ft_itoa_base(n, 8);
    f->nprinted += write(1, s, nbrlen);
    if (f->hash == 1)
        paddingleftaligned(nbrlen, differenceog, f);
    else
        paddingleftaligned(nbrlen, differenceog, f);
}

void    ifoctal(t_struct *f, va_list ap)
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
        right_aligned_octal(n, f);
    else if (f->minus == 1)
        left_aligned_octal(n, f);
}