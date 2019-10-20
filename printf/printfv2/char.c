/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:38:52 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/16 12:38:55 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ifpercent()
{
	write(1, "%", 1);
}


void	ifchar(int i, t_struct *f, va_list ap)
{
	unsigned char c;
//	int num;

	/*we use int here because it is 4 bytes. any pointer is 4 bytes
	so techinically any pointer variable would work as well.
	the second parameter of va_arg is the type of argument to be returned*/
	c = (unsigned char)va_arg(ap, int);
//	c = 'a';

	if(f->width && f->minus == 0)
	{
		write(1, " ", 1);
		/*
		num = f->width - 1;
		while (num > 0)
		{
			write(1, " ", 1);
			num--;
		}
		write(1, &c, 1);*/
	}/*
	else if(f->width && f->minus == 1)
	{
		num = f->width - 1;
		write(1, &c, 1);
		while (num > 0)
		{
			write(1, " ", 1);
			num--;
		}
	}
	*/
	write(1, &c, 1);
	i++;
}