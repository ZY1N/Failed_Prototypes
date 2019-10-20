/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:38:55 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/16 13:38:57 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


/*converstion from printf*/
void	conversions(char c, int i, va_list ap, t_struct *f)
{
	
	if(c == 'c')
		ifchar(i, f, ap);/*
	else if(c == 's')
		ifstring(i, ap);
	else if(c == 'p')
		ifchar(i, ap);
	else if(c == 'd')
		ifchar(i, ap);
	else if(c == 'i')
		ifchar(i, ap);
	else if(c == 'o')
		ifchar(i, ap);
	else if(c == 'u')
		ifchar(i, ap);
	else if(c == 'x')
		ifchar(i, ap);
	else if(c == 'X')
	ifchar(i, ap);
	else if(c == 'f')
		ifchar(i, ap);*/
	else if(c == '%')
		ifpercent();
}
