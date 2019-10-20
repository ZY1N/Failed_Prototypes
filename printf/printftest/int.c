/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:17:38 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/25 16:17:41 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base2(intmax_t value, int base)
{
	char	*s;
	long	n;
	int		sign;
	int		i;

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


int     signed_nbr_len(intmax_t n, int base)
{
    int nbrlen;

    nbrlen = 0;
    if (n < 0)
    {
        n = -n;
        nbrlen++;
    }
    while(n)
    {
        n = n / base;
        nbrlen++;
    }
    return(nbrlen);
}



/*
void    right_aligned_int(t_struct *f, int widthp, int precisionp, int hexlenp, char *s, char c, int sign)
{

    if (sign == NEGATIVE && f->zero)
        c = '0';


    if (sign)
    {
        if (sign == POSITIVE && ((f->zero && widthp) || !widthp))
        {
            f->nprinted += write(1, "+", 1);
            sign -= POSITIVE;
        }
        else if (sign == NEGATIVE && ((f->zero && widthp) || !widthp))
        {
            f->nprinted += write(1, "-", 1);
            sign -= NEGATIVE;
        }
    }
    while(widthp > 0)
    {
        f->nprinted += write(1, &c, 1);
        widthp--;
    }

    if (sign)
    {
        if (sign == POSITIVE)
        {
            f->nprinted += write(1, "+", 1);
            sign -= POSITIVE;
        }
        else if (sign == NEGATIVE)
        {
            f->nprinted += write(1, "-", 1);
            sign -= NEGATIVE;
        }
    }
    while (precisionp > 0)
	{
		f->nprinted += write(1, "0", 1);
	   	precisionp--;	
    }
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
}
*/

/*

void	left_aligned_int(t_struct *f, int widthp, int precisionp, int hexlenp, char *s, int sign)
{
    if (sign == POSITIVE)
        f->nprinted += write(1, "+", 1);
    else if (sign == NEGATIVE)
        f->nprinted += write(1, "-", 1);
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

void    right_aligned_int()

void    formatextractionint(intmax_t n, t_struct *f)
{
    int precisionp;
    int intlenp;
    int widthp;
    char *s;
    char c;
    int signTF;
    int sign;

    signTF = 0;
    sign = 0;
    if (n < 0 || f->plus)
        signTF = 1;
    if (n < 0)
        sign = NEGATIVE;
    else if (n >= 0 && f->plus)
        sign = POSITIVE;
    

    if(f->zero && !f->precisionTF)
        c = '0';
    else
        c = ' ';
    if (n < 0)
        n = -n;
    s = ft_itoa_base2(n, 10); 

    intlenp = signed_nbr_len(n, 10);
    printf("\n\n\nn: %jd\n\n\n", n);
    printf("\n\noctlenp before: %d\n\n", intlenp);
     if (n == 0)
     {
        intlenp = 1;
        if (f->precisionTF && f->precision == 0)
            intlenp = 0;
     }    
    printf("\n\noctlenp after: %d\n\n", intlenp);
    printf("\n\nnumber int %ju\n\n", n);
    if(f->precisionTF && f->precision > intlenp)
        precisionp = f->precision - intlenp;
    else
        precisionp = 0;
    widthp = f->width - (precisionp + intlenp + signTF);
    printf("\n\nwidthp: %d precisionp: %d octlenp: %d\n\n", widthp, precisionp, intlenp);
  printf("\n\n\n\nstring %s\n\n", s);
    if (f->minus == 0)
        right_aligned_int(f, widthp, precisionp, intlenp, s, c, sign);
    else if (f->minus == 1)
        left_aligned_int(f, widthp, precisionp, intlenp, s, sign);
}*/



void    right_aligned_int(t_struct *f, int padding, int precision, int intlen, char *s, char c, int sign)
{
    char signc;

    signc = '\0';
    if (sign == POSITIVE)
        signc = '+';
    else if (sign == NEGATIVE)
        signc = '-';


    //print sign here
      //  check to see if there is padding with zero if there is print it here 
        //or if there is no padding at all 

   //   printf("\n\nsign: %d padding: %d precision: %d intlen: %d string: %s\n\n", sign, padding, precision, intlen, s);
  // printf("\nblank: %d\n", f->space);

   // printf("\n\nnprinted1: %d\n\n", f->nprinted);

    if (padding > 0 && c == '0' /*&& sign != '\0'*/)
    {
        if (f->space)
        {
            f->nprinted += write(1, " ", 1);
            f->space = 0;
        }
    //    printf("\n\nnprinted1.1 : %d\n\n", f->nprinted);
        if (sign != '\0')
            f->nprinted += write(1, &signc, 1);
     //   printf("\n\nnprinted1.2: %d\n\n", f->nprinted);
        sign -= sign;
    }
    else if (padding <= 0 && signc != '\0')
    {
        f->nprinted += write(1, &signc, 1);
     //   printf("\n\nnprinted1.3: %d\n\n", f->nprinted);
        sign -= sign;
    }
   // printf("\n\nnprinted1: %d\n\n", f->nprinted);
 

    while (padding > 0)
    {
        f->nprinted += write(1, &c, 1);
        padding--;        
    }

   // printf("\n\nnprinted2: %d\n\n", f->nprinted);

    if (f->space != 0)
        f->nprinted += write(1, " ", 1);

    if (sign != 0 && signc != '\0')
        f->nprinted += write(1, &signc, 1);
    
   // printf("\n\nnprinted3: %d\n\n", f->nprinted);
    while (precision > 0)
    {
        f->nprinted += write(1, "0", 1);
        precision--;
    }
   // printf("\n\nnprinted4: %d\n\n", f->nprinted);

    f->nprinted += write(1, s, intlen);

    //printf("\n\nnprinted5: %d\n\n", f->nprinted);
}



void	left_aligned_int(t_struct *f, int widthp, int precisionp, int hexlenp, char *s, int sign)
{

    //if (f->space && sign == 0)
      //    widthp++;
    if (f->space)
        f->nprinted += write(1, " ", 1);

    if (sign == POSITIVE)
        f->nprinted += write(1, "+", 1);
    else if (sign == NEGATIVE)
        f->nprinted += write(1, "-", 1);
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




void    formatextractionint(intmax_t n, t_struct *f)
{
    int sign;
    int padding;
    int precision;
    int intlen;
    char *s;
    char c;


    sign = 0;


    if(f->zero && !f->precisionTF)
        c = '0';
    else
        c = ' ';
    

    if (f->plus && n >= 0)
        sign = POSITIVE;
    else if (n < 0)
    {
        sign = NEGATIVE;
        n = n * -1;
    }

   // printf("\n\nspace before %d    plus?? %d\n\n\n", f->space, f->plus);

    if(f->space && sign != 0)
        f->space = 0;

   // printf("\n\nspace after %d\n\n\n", f->space);


    s = ft_itoa_base2(n, 10);

    intlen = signed_nbr_len(n, 10);

    if (n == 0)
        intlen = 1;
    if (f->precisionTF && f->precision == 0)
        intlen = 0;

   // printf("\n\n\n%s\n\n\n\n", s);


    if(f->precisionTF && f->precision > intlen)
        precision = f->precision - intlen;
    else
        precision = 0; 
    
    
    if (sign != 0)
        padding = f->width - (precision + intlen + 1 + f->space);
    else
        padding = f->width - (precision + intlen + f->space);
    
    
  //   printf("\n\nsign: %d padding: %d precision: %d intlen: %d string: %s\n\n", sign, padding, precision, intlen, s);
   //printf("\nblank: %d\n", f->space);
    
    if (f->minus == 0)
        right_aligned_int(f, padding, precision, intlen, s, c, sign);
    if (f->minus == 1)
        left_aligned_int(f, padding, precision, intlen, s, sign);


}

void ifint(t_struct *f, va_list ap)
{
    intmax_t n;

    n = 0;
    if (f->length == 0)
        n = (int)va_arg(ap, int);
    else if (f->length == HH)
        n = (signed char)va_arg(ap, int);
    else if (f->length == H)
        n = (short int)va_arg(ap, int);
    else if (f->length == LL)
    {
        n = (long long int)va_arg(ap, long long int);
      //  printf("\n\n%lld\n\n", n);
    }
    else if (f->length == L)
        n = (long int)va_arg(ap, long int);
    
    formatextractionint(n, f);
}