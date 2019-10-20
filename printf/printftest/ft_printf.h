/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:18:04 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/18 17:04:05 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <float.h>

#define H   1
#define HH  2
#define L   3
#define LL  4
#define J   5
#define Z   6
#define BIGL 7 

#define POSITIVE 66
#define NEGATIVE 88

#define cconversions "cspdiouxXf%"
#define cflags "#-+ .*0123456789hljz"
#define allsymbols "cspdiouxXf%#-+ .*0123456789hljz"

/*possible improvement is to shrink the data structure to chars or bitwise to save
space, but this works as well*/
typedef struct s_struct
{
    char *format;

    int nprinted;

    int i;
    int len;
    
    int minus;
    int plus;
    int space;
    int zero;
    int hash;

    int width;
    int precisionTF;
    int precision;
    int length;
}   t_struct;

//void    modifiers(const char *format, t_struct *f, va_list ap);
void    modifiers();
void	conversions(char c, int i, va_list ap, t_struct *f);
void	ifchar(t_struct *f, va_list ap);
void    ifpercent();
void    ifstring();
void    writeblanks(int n);
void    ifpointer();
void    ifint(t_struct *f, va_list ap);
char	*ft_itoa_base(uintmax_t value, uintmax_t base);
void    ifoctal();
int     unsigned_nbr_len(uintmax_t n, int base);
void    ifhex(t_struct *f, va_list ap, char c);
void    writezeros(int n);
void ifudecint(t_struct *f, va_list ap);
void    ifloat(t_struct *f, va_list ap);
char		*ft_stradd(char *a, char *b);
#endif
