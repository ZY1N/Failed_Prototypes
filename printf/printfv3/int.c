/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:27:21 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/25 16:28:10 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* */

void	rightsideint(t_struct *f, char *s)
{
	int i;

	i = ft_strlen(s);
	if(f->precisionTF == 0)
	{
		if (f->space && !f->width)
			f->nprinted += write(1, " ", 1);
		if (f->plus && f->zero)
			f->nprinted += write(1, "+", 1);
		if (f->zero)
			f->nprinted += write(1, "-", 1);		
	}
	else if(f->precisionTF == 1)
	{
		if (f->plus && f->width)
			f->width--;
		while (f->width)
		{
			f->nprinted += write(1, " ", 1);
			f->width --;
		}
		if (f->plus)
			f->nprinted += write(1, "+", 1);
	}

}

//void	leftsideint(/*t_struct *f, char *s*/)
//{
//	printf("jadsadflk");
//}

void	ifint(t_struct *f, va_list ap)
{
	intmax_t num;
	char *s;

	if (f->length == HH)
		num = (signed char)va_arg(ap, int);
	else if (f->length == H)
		num = (short)va_arg(ap, int);
	else if (f->length == LL)
		num = (long long)va_arg(ap, long long);
	else if (f->length == L)
		num = (long)va_arg(ap, long);
	else
		num = (int)va_arg(ap, int);
	s = ft_itoa_base(num, 10);
	
	if (f->minus == 0)
		rightsideint(f, s);
//	else if(f->minus == 1)
		//leftsideint(f, s);

/*
	while(*s)
	{
		write(1, s, 1);
		s++;
	}	*/
}