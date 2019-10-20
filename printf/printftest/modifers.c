/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:47:24 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/16 13:47:27 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*for all of these check out this link for explaination http://www.cplusplus.com/reference/cstdio/printf/*/

/*we can do this all because  this is how the original printf is defined aka :
    %[flags][width][.precision][length]specifier in that order
    flags = "-+ #0"
    width = "number *"
    precision = ".number .*"
*/


void    flags(const char *format, t_struct *f)
{
    while(ft_strchr("-+ #0", format[f->i]))
    {
        /*think of the struct as an menu, we are checking off the options in order to 
        pass it to the other ones to read first*/
        if(format[f->i] == '-')
            f->minus = 1;
        if(format[f->i] == '+')
            f->plus = 1;
        if(format[f->i] == ' ')
            f->space = 1;
        if(format[f->i] == '#')
            f->hash = 1;
        if(format[f->i] == '0')
            f->zero = 1;
        f->i++;
     }
    /*if there is a place sign and a space is also there we get rid of the space if
    the plus sign is there. by default a plus sign is not shown*/
    if(f->plus == 1)
        f->space = 0;
}

void    width(const char *format, t_struct *f, va_list ap)
{
    if(format[f->i] == '*')
    {
        /*i am trying to pull out the width with va_arg*/
        f->width = va_arg(ap, int);
        /*negative width means that we want the width but also
        an negative sign, so we convert it here to pass the minus
        to the structure and turn the width positive*/
        if (f->width < 0)
        {
             f->minus = 1;
             f->width = -(f->width);
        }
        while (format[f->i] == '*')
            f->i++;
    }
    if(format[f->i] >= '0' && format[f->i] <= '9')
    {
        f->width = ft_atoi(&format[f->i]); /*atoi gets all of the digits until it isn't a number anymore*/
        while (format[f->i] >= '0' && format[f->i] <= '9')
        {
            f->i++;
            if (format[f->i] == '*')
            {
                if (f->width < 0)
                {
                     f->minus = 1;
                     f->width = -(f->width);
                }
                while (format[f->i] == '*')
                    f->i++;
            }
        }
    }
}

void    precision(const char *format, t_struct *f, va_list ap)
{
    int p;
    int i;

    i = f->i;
    if (format[i] == '.')
    {
        i++;
        f->precisionTF = 1;
        if (format[i] >= '0' && format[i] <= '9')
        {
            f->precision = ft_atoi(&format[i]);
            while (format[i] >= '0' && format[i] <= '9')
                i++;
        }
        else if (format[f->i] == '*')
        {
            p = va_arg(ap, int);
            /*check to see if precision is positive or negative
            negaticve doent work and unchecks the precision flags*/
            if (p >= 0)
                f->precision = p;
            else if (p < 0)
                f->precisionTF = 0;
            while (format[f->i] == '*')
                i++;
        }
    }
    /*checks to see if the precision is true and there is no minus symnbol then 
    the number of space is 0*/
    //if (f->precisionTF == 1 && f->minus == 0)
      //  f->space = 0;
    f->i = i;
}

void    length(const char *format, t_struct *f)
{
    int i;
    int extra;

    extra = 0;
    i = f->i;
    if (ft_strchr("hlLjz", format[i]))
    {
        if(format[i] == 'h')
        {
            if(format[i + 1] == 'h')
                f->length = HH;
            else if (format[i - 1] != 'h')
                f->length = H;
        }
        if(format[i] == 'l')
        {
            if(format[i + 1] == 'l')
                f->length = LL;
            else if (format[i - 1] != 'l')
                f->length = L;
        }
        if(format[i] == 'j')
            f->length = J;
        if(format[i] == 'z')
            f->length = Z;
        if(format[i] == 'L')
            f->length = BIGL;
    }
    while(ft_strchr("hlLjz", format[i]))
        i++;
    f->i = i;
}

void    printstruct(t_struct *f)
{
    printf("format: %s\n", f->format);
    printf("i: %i\n", f->i);
    printf("len: %i\n", f->len);

    printf("minus: %i\n", f->minus);
    printf("plus: %i\n", f->plus);
    printf("space: %i\n", f->space);
    printf("zero: %i\n", f->zero);
    printf("hash: %i\n", f->hash);

    printf("width: %i\n", f->width);
    printf("precisionTF: %i\n", f->precisionTF);
    printf("precision: %i\n", f->precision);
    printf("length: %i\n", f->length);

}

void    modifiers(const char *format, t_struct *f, va_list ap)
{
    flags(format, f);
    width(format, f, ap);
    precision(format, f, ap);
    length(format, f);
   /* printstruct(f);*/
}