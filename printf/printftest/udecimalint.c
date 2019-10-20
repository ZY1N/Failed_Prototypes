/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udecimalint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:24:54 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/31 19:25:20 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"


int     signed_nbr_len2(intmax_t n, int base)
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


void    right_aligned_uint(t_struct *f, int padding, int precision, int intlen, char *s, char c, int sign)
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



void	left_aligned_uint(t_struct *f, int widthp, int precisionp, int hexlenp, char *s, int sign)
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




void    formatextractionuint(intmax_t n, t_struct *f)
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


    s = ft_itoa_base(n, 10);

    intlen = signed_nbr_len2(n, 10);

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
        right_aligned_uint(f, padding, precision, intlen, s, c, sign);
    if (f->minus == 1)
        left_aligned_uint(f, padding, precision, intlen, s, sign);


}

void ifudecint(t_struct *f, va_list ap)
{
    uintmax_t n;

    n = 0;
    if (f->length == 0)
        n = (unsigned int)va_arg(ap, unsigned int);
    else if (f->length == HH)
        n = (unsigned char)va_arg(ap, int);
    else if (f->length == H)
        n = (unsigned short int)va_arg(ap, int);
    else if (f->length == LL)
    {
        n = (unsigned long long int)va_arg(ap, long long int);
      //  printf("\n\n%lld\n\n", n);
    }
    else if (f->length == L)
        n = (unsigned long int)va_arg(ap, long int);
    
    formatextractionuint(n, f);
}
