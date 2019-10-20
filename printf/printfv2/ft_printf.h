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

#define H   1
#define HH  2
#define L   3
#define LL  4
#define J   5
#define Z   6

/*possible improvement is to shrink the data structure to chars or bitwise to save
space, but this works as well*/
typedef struct s_struct
{
    char *format;

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
    char length;
}   t_struct;

//void    modifiers(const char *format, t_struct *f, va_list ap);
void    modifiers();
void	conversions(char c, int i, va_list ap, t_struct *f);
void	ifchar(int i, t_struct *f, va_list ap);
void    ifpercent();

#endif
