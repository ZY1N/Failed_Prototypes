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

/*
void    padding(int nbrlen, int difference, t_struct *f, char c)
{ 
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
    if(f->hash && f->width && !f->precision)
        f->width--;
    padding(nbrlen, difference, f, c);
    if (f->hash == 1 && n != 0)
    {
        f->nprinted += write(1, "0", 1);
        difference --;
    }
    while(difference > 0)
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
} */






/*
void formatextractionoctal(uintmax_t n, t_struct *f)
{
    int octlenp;
    char *s;
    int precisionp;
    int widthp;
    int hashheading;
    char c;

    if(f->zero && !f->precisionTF)
        c = '0';
    else
        c = ' ';
    hashheading = 1;
    if (n != 0)
        octlenp = unsigned_nbr_len(n, 8);
    else
        octlenp = 1;
    s = ft_itoa_base(n, 8);
    
    precisionp = f->precision - octlenp;
    if (f->precisionTF && f->precision == 0)
		octlenp = 0;
    if (precisionp > 0)
       widthp = f->width - (octlenp + precisionp);  
    else 
        widthp = f->width - octlenp;
    
    if (n == 0)
        f->hash = 0;

    if (f->hash && f->precision > 0)
        precisionp--;
    else if (f->hash && widthp > 0)
        widthp--;



    if (f->minus == 0)
        right_aligned_octal(f, widthp, precisionp, octlenp, s, c);
    else if (f->minus == 1)
        left_aligned_octal(f, widthp, precisionp, octlenp, s);
}*/

void    right_aligned_octal(t_struct *f, int widthp, int precisionp, int octlenp, char *s, char c, int hash)
{
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
    if (hash == 1)
        f->nprinted += write(1, "0", 1);
	f->nprinted += write(1, s, octlenp);
}


void	left_aligned_octal(t_struct *f, int widthp, int precisionp, int octlenp, char *s, int hash)
{
	while (precisionp > 0)
	{
		f->nprinted += write(1, "0", 1);
		precisionp--;	
	}
    if (hash == 1)
        f->nprinted += write(1, "0", 1);
	f->nprinted += write(1, s, octlenp);
	while(widthp > 0)
	{
		f->nprinted += write(1, " ", 1);
		widthp--;
	}
} 

void    formatextractionoctal(uintmax_t n, t_struct *f)
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
    
    //printf("\n\nbefore: %hhd\n\n", n);

    s = ft_itoa_base(n, 8);

    //printf("\n\nafteritoabase as string %s \n\n", s);
    hashp = 0;
    octlenp = unsigned_nbr_len(n, 8);
    if (f->hash)
        hashp = 1;
    
 //   printf("\n\noctlenp before: %d\n\n", octlenp);

     if (n == 0)
    {
        octlenp = 1;
        if (hashp == 1)
            octlenp = 0;
        if (f->precisionTF && f->precision == 0)
            octlenp = 0;
    }    

  //  printf("\n\noctlenp after: %d\n\n", octlenp);

//    printf("\n\nnumber int %ju\n\n", n);
    
    if(f->precisionTF && f->precision > octlenp)
        precisionp = f->precision - octlenp - hashp;
    else
        precisionp = 0;
    
   
    
    widthp = f->width - (precisionp + octlenp) - hashp;


 //   printf("\n\nwidthp: %d precisionp: %d octlenp: %d hashp: %d\n\n", widthp, precisionp, octlenp, hashp);

  //  printf("\n\n\n\nstring %s\n\n", s);

    if (f->minus == 0)
        right_aligned_octal(f, widthp, precisionp, octlenp, s, c, hashp);
    else if (f->minus == 1)
        left_aligned_octal(f, widthp, precisionp, octlenp, s, hashp);

}

void    ifoctal(t_struct *f, va_list ap)
{
    unsigned long n;

    n = 0;
    if (f->length == 0)
        n = va_arg(ap, unsigned int);
    else if (f->length == HH)
    {
        n = (unsigned char)va_arg(ap, unsigned int);
        //printf("%lu\n", n);
    }
    else if (f->length == H)
        n = (unsigned int)va_arg(ap, unsigned int);
    else if (f->length == LL)
        n = (unsigned long long)va_arg(ap, unsigned long long);
    else if (f->length == L)
        n = (unsigned long)va_arg(ap, unsigned long);
    formatextractionoctal(n, f);
}