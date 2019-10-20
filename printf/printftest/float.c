/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:53:58 by yinzhang          #+#    #+#             */
/*   Updated: 2019/06/03 14:22:03 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>
#include <limits.h>


long double 	power(intmax_t n, int i)
{

	long		k;
	long double	res;

	res = n;
	k = 0;
	if (i == 0)
		return (1);
	while (k < i - 1)
	{
		res = res * n;
		k++;
	}
	return (res);
}



int     signed_nbr_len3(intmax_t n, int base)
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



char	*ft_itoa_base3(uintmax_t value, int base)
{
	char				*s;
	uintmax_t	n;
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

char		*itoa_base(long long int num, int base, int flag)
{
	char			alloc[50];
	char			*res;
	int				i;
	int				neg;

	neg = 1;
	res = (flag == 0) ? "0123456789abcdef" : "0123456789ABCDEF";
	if (num == 0)
		return (ft_strdup("0"));
	i = 48;
	alloc[49] = '\0';
	if (num < 0)
		neg = -1;
	while (num != 0)
	{
		alloc[i--] = res[neg * (num % base)];
		num /= base;
	}
	return (ft_strdup(&(alloc[++i])));
}

char	*ftoa(long double f, int n)
{
	char	*flpt;
	char	*intpt;
	long	fl;
	long	i;
	char	*neg;

	neg = 0;
	if (f < 0)
		neg++;
	i = (long long)f;
	intpt = itoa_base(i, 10, 0);
	f = f - (long double)i;
	f = (f * power(10, n));
	fl = (f >= 0) ? (long)(f + 0.5) : (long)(f - 0.5);
	flpt = itoa_base(fl, 10, 0);
	if (neg)
		intpt = ft_stradd(ft_strdup("-"), intpt);
	if (n == 0)
		return (intpt);
	intpt = ft_stradd(intpt, ft_strdup("."));
	intpt = ft_stradd(intpt, flpt);
	return (intpt);
}
/*
int     zerosafterdecimal(long double n)
{
    int i;
    i = 0;
    int  x;

    x = power(n, 6);
    int a = 0;
    x = 1.000000;
    printf("\nlong double n; %Lf\n", n);
    if (n == 0)
        return(0);
    while (n !=  x)
    {
        
        n = n * 10;
        a = (int)n;
        printf("\nn: %d\n", a);
        if (n >= x)
            break;
        i++;
        if (a > 0)
            break;
    }
    if (n / 10 > 1)
        i--;
    printf("\nn: %Lf\n", n);

    if (n < 0.1)
        i = 1;
    else if (n < 0.01)
        i = 2;
    else if (n < 0.001)
        i = 3;
    else if (n < 0.0001)
        i = 4;
    else if (n < 0.00001)
        i = 5;
    else if (n < 0.000001)
        i = 6;
    else if (n < 0.0000001)
        i = 7;
    else if (n >= 0.0000000099999999999)
        i = 8;
    else if (n >= 0.0000000009999999999)
        i = 9;
    else if (n >= 0.0000000000999999999)
        i = 10;
    else if (n >= 0.0000000000099999999)
        i = 11;
    else if (n >= 0.0000000000009999999)
        i = 12;
    else if (n >= 0.0000000000000999999)
        i = 13;
    else if (n >= 0.0000000000000099999)
        i = 14;
    else if (n >= 0.0000000000000009999)
        i = 15;
    else if (n >= 0.0000000000000000999)
        i = 16;
    else if (n >= 0.0000000000000000099)
        i = 17;
    else if (n >= 0.0000000000000000009)
        i = 18;
    
    printf("i: %d", i);
    return (i);
} */


void    rightalignedf(t_struct *f, char *s1, char *s2, int zeros, int padding, int precisionaddon, char c, int signint, char sign, int precision, int dot)
{
    char space;

  //  printf("\nhere i am");

    if (padding > 0 && c == '0')
    {
        if (signint == 1 && sign)
        {
        f->nprinted += write(1, &sign, 1);
        sign = 'a';
        f->space = 0;
        }
    }


/*
    if (f->space && c != '0')
    {
        f->nprinted += write(1, " ", 1);
        padding--;
    }
    else if (f->space && c == '0')
    {
        f->nprinted += write(1, " ", 1);
        padding--;
   }
*/
  //  printf("space: %d\n", f->space);



   // printf("problemarea");
/* PROBLEM IS RIGHT HERE COME FIX IT */


    //printf("space: %d\n", f->space);

    space = '0';
    if (f->space == 1 && (f->zero == 0 || f->precision))
        space = ' ';
  //  else if (f->space == 1 && f->zero == 1 && (sign == '+' || sign == '-'))
    //    space = '0';
    
  // printf("precision: %d\n", f->precision);
    if (sign == '-' || f->precision == 0)
    {
        
        if (f->precision == 0 && f->space)
        {
           // padding--;
            f->space = 1;
        }
        else
        f->space = 0;
            //f->space = 1;
        //padding--;
       // if (f->plus == 0)
    }
     //printf("sign %d\n", f->precision);
    if (f->precision == 0 && f->precisionTF == 1)
        space = ' ';
    
    //printf("precision%d\n",precision);
    //printf("f->zero%d\n", f->zero);
    //printf("f->wdith %d", f->width);
    if (f->precision == 0 && f->zero == 0 && f->width !=0)
        space = ' ';

    //printf("\nspaceadsf: [%c]\n", space);
    //printf("\nspace333: %d\n", f->space);

    if (f->space == 1)
    {
        //printf("space666: [%c]", space);
        f->nprinted += write(1, &space, 1);
        padding--;
    }
    //printf("space: %d\n", f->space);
     //   printf("padding: %d\n", padding);





/*
    if (f->space == 1 && c != '0' && sign != '-')
    {
        f->nprinted += write(1, " ", 1);
        padding--;
    }
    else if (f->space == 1 && sign == '-' && signint == 1 && c == '0' && precision > 0)
    {
        f->nprinted += write(1, "0", 1);
        padding--;
    }
*/







  //  padding = 10;
   //printf("padding %d\n", padding);
    while (padding > 0)
    {
       // printf("IM STUCK HERE");
        f->nprinted += write(1, &c, 1);
        padding--;
    }

  //    printf("77777\n");

    if (sign != 'a' && signint)
    {
        if (signint == 1 && sign)
        f->nprinted += write(1, &sign, 1);
    }

 //   printf("\n77777");
   while (*s1)
   {
       f->nprinted += write(1, s1, 1);
       s1++;
   }

 //   printf("adsfadsfaf%d\n", f->precisionTF);

    //if ((ft_strlen(s2) > 0 && *s2) || (f->precisionTF == 1 && f->precision != 0) || f->hash)
       // f->nprinted += write(1, ".", 1);
        if (dot == 1 || f->hash)
            f->nprinted += write(1, ".", 1);
/*

    if (*s2 || precisionaddon > 0 && precision > 0)
    {
        f->nprinted += write(1, ".", 1);
        if (zeros >= 0)
            precision--;
    }
    */
    
   // printf("zeros: %d", zeros);
   // printf("precision: %d", precision);

    while (zeros > 0 && precision != 0)
    {
        f->nprinted += write(1, "0", 1);
        zeros--;
        precision--;
    }

  //    printf("%s\n", s2);
  //  printf("sting2: %s", s2);
   while (*s2 && precision != 0)
    {
        f->nprinted += write(1, s2, 1);
        s2++;
        precision--;
    }


   // printf("addon: %d", precisionaddon);
    while (precisionaddon > 0)
    {
        f->nprinted += write(1, "0", 1);
        precisionaddon--;
    }    
}

void    leftalignedf(t_struct *f, char *s1, char *s2, int zeros, int padding, int precisionaddon, char c, int signint, char sign, int precision, int dot)
{
    
    if (f->space && sign != '-')
    {
        f->nprinted += write(1, " ", 1);
        padding--;
        f->space = 0;
    }
    if (signint == 1 && sign)
        f->nprinted += write(1, &sign, 1);

    while (*s1)
    {
        f->nprinted += write(1, s1, 1);
        s1++;
    }

   // if ((ft_strlen(s2) > 0 && *s2) || (f->precisionTF == 1 && f->precision != 0) || f->hash )
       // f->nprinted += write(1, ".", 1);
    if (dot == 1 || f->hash)
       f->nprinted += write(1, ".", 1); 

/*
    if (*s2 || precisionaddon > 0 && precision > 0)
    {
        f->nprinted += write(1, ".", 1);
        precision--;
    }*/
    while (zeros > 0 && precision != 0)
    {
        f->nprinted += write(1, "0", 1);
        zeros--;
        precision--;
    }

    while (*s2 && precision != 0)
    {
        f->nprinted += write(1, s2, 1);
        s2++;
        precision--;
    }

    if (f->space && sign == '-' && precision > 0)
    {
        f->nprinted += write(1, " ", 1);
        padding--;
        f->space = 0;
    }


    while (precisionaddon > 0)
    {
        f->nprinted += write(1, "0", 1);
        precisionaddon--;
    }    
    while (padding > 0)
    {
        f->nprinted += write(1, &c, 1);
        padding--;
    }    
    
}




void    formatextractionf(long double n, t_struct *f)
{
    char *s1;
    char *s2;
    long long ss2;
    int precision;
    long double i;
    long double fl;
    int zeros;
    int precisionaddon;
    int padding;
    int beforedecimalnbr;
    char c;
    char sign;
    int  signint;
    int hash;
    int dot;

    long long i2;
    long long fl2;



    signint = 0;
    if(f->plus)
        signint = 1;
    sign = ' ';
    if (n < 0)
    {
        sign = '-';
        n = - n;
        signint = 1;
    }
    else if (n > 0 && f->plus)
        sign = '+';



    precision = 6;
    if (f->zero == 1)
        c = '0';
    else
        c = ' '; 
    
    if (f->minus)
        c = ' ';

    if (f->precisionTF == 1 && f->precision >= 0)
        precision = f->precision;

    i = (long long)n;
    i2 = i;
   // printf("\nlong long i %ld\n", i);


    //intpt = itoa_base(i, 10, 0);
	//f = f - (long double)i;
	//f = (f * power(10, n));
	//fl = (f >= 0) ? (long)(f + 0.5) : (long)(f - 0.5);
	//flpt = itoa_base(fl, 10, 0);





    s1 = ft_itoa_base3(i2, 10);

    //printf("asdfadsfads");

    n = n - (long double)i;

    //printf("\nlong long i %Lf\n", n);
    precisionaddon = 0;

    //printf("66666");
    if (n == 0)
       precisionaddon = precision - 1;

 
   // printf("\nbeforepower: %Lf\n", n);
    n = (n * power(10, precision));
     // printf("\nn after power: %Lf\n", n);
    fl = (n >= 0) ? (long)(n + 0.5) : (long)(n - 0.5);



   // printf("\n8888\n");

    if (fl == power(10, precision) && fl != 0)
    {
        s1 = ft_itoa_base3(i + 1, 10);
        fl = 0;
        if (fl == 0)
        {
            precisionaddon = precision - 1;
        }
    }


    //printf("\n999\n");
    
    s2 = ft_itoa_base(fl, 10);

   // printf("%s\n", s2);
    //if (precision == 0)
    //{
    //    s2 = "\0";
   // }


    if (precision != 0)
        zeros = precision - signed_nbr_len3(fl, 10);
    
    else
        zeros = 0;

   //printf("\n48454545454558\n");



    beforedecimalnbr = signed_nbr_len3(n, 10);




    if (fl == 0)
        zeros--;

    hash = 0;
    if (f->hash)
        hash = 1;
    if (f->hash && ft_strlen(s2) > 0)
        hash = 0;
    
    dot = 0;
    if ((ft_strlen(s2) > 0 && precision != 0) || f->hash )
        dot = 1; 


    //printf("dot : %d \n", dot);
   // printf("precision: %d", precision);
    //printf("beforenumbeer : %d", beforedecimalnbr);

    if (precision != 0)
        padding = f->width - f->precision - beforedecimalnbr - hash - signint - dot;
    else
        padding = f->width - f->precision - beforedecimalnbr - hash - signint - dot -  1;

   // printf("\nherhe");
   // if (ft_strlen(s2) + ft_strlen(s1) + signint == f->width)
       // f->space = 0;

    //printf("\n\nadfsasdfafds\n\n");

  // printf("\npadding: %d\n", padding);

    if(f->minus == 0)
    {
       // printf("\nenteredfromhere");
        rightalignedf(f, s1, s2, (zeros - precisionaddon), padding, precisionaddon, c, signint, sign, precision, dot);
        //printf("\ncomeouthere");
    }
    else if (f->minus == 1)
        leftalignedf(f, s1, s2, zeros - precisionaddon, padding, precisionaddon, c, signint, sign, precision, dot);
}

/*
void printlbdlmax(t_struct *f)
{
    f->nprinted += write(1, LDBL_MAX , 372);
}

void printdbl_max(t_struct *f)
{
    printf("%f", DBL_MAX);
    
}*/


void ifloat(t_struct *f, va_list ap)
{
    long double n;
    
    //printf("jasdfklkadlsf");

    if (f->length == 0)
        n = (long double)va_arg(ap, double);
    else if (f->length == BIGL)
//        printf("6666");
        n = (long double)va_arg(ap, long double);
//    printf("\n%Lf\n", n);
/*
    if (n == LDBL_MAX)
        printlbdlmax(f);
    else if (n == DBL_MAX)
        printdbl_max(f);
    else */
    formatextractionf(n, f);
}





/*
void    rightalignedf(t_struct *f, char *s, int padding, char c, int precisionaddon)
{
    while (padding > 0)
    {
        f->nprinted += write(1, &c, 1);
        padding--;
    }
    while (*s)
    {
        f->nprinted += write(1, s, 1);
        s++;
    }
    while (precisionaddon > 0)
    {
        f->nprinted += write(1, "0", 1);
        precisionaddon--;
    }
}


void    leftalignedf(t_struct *f, char *s, int padding, char c, int precisionaddon)
{
    while (*s)
    {
        f->nprinted += write(1, s, 1);
        s++;
    }
    while (padding > 0)
    {
        f->nprinted += write(1, &c, 1);
        padding--;
    }    
    
}

void    formatextractionf(long double n, t_struct *f)
{
    char *s;
    int     precision;
    int     beforedecimalnbr;
    int     padding;
    char c;
    int     precisionaddon;

    if (f->zero == 1)
        c = '0';
    else
        c = ' ';

    precision = 6;


    if (f->precisionTF == 1 && f->precision >= 0)
        precision = f->precision;


    s = ftoa(n, precision); 

    beforedecimalnbr = signed_nbr_len3(n, 10);

    precisionaddon = 0;
    if (n - (long long)n == 0)
    {
       precisionaddon = precision - 1;
    }


    
    if (precision <= 0)
        padding = f->width - precision - beforedecimalnbr;
    else
        padding = f->width - precision - beforedecimalnbr - 1;

    if(f->minus == 0)
        rightalignedf(f, s, padding, c, precisionaddon);
    else if (f->minus == 1)
        leftalignedf(f, s, padding, c, precisionaddon);
}



void ifloat(t_struct *f, va_list ap)
{
    long double n;

    if (f->length == 0)
        n = (long double)va_arg(ap, double);
    else if (f->length == L)
        n = (long double)va_arg(ap, long double);


    formatextractionf(n, f);
}
*/
