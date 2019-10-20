/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:17:26 by yinzhang          #+#    #+#             */
/*   Updated: 2019/05/21 10:55:58 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft/libft.h"

void	bezerostruct(t_struct *list)
{
	list->i = 0;
	list->len = 0;
	list->minus = 0;
	list->plus = 0;
	list->space = 0;
	list->zero = 0;
	list->hash = 0;
	list->width = 0;
	list->precisionTF = 0;
	list->precision = 0;
	list->length = 0;
}

/*resets everything except for i, which indicates which va_list item it is*/
void	bezerostruct2(t_struct *list)
{
	list->len = 0;
	list->minus = 0;
	list->plus = 0;
	list->space = 0;
	list->zero = 0;
	list->hash = 0;
	list->width = 0;
	list->precisionTF = 0;
	list->precision = 0;
	list->length = 0;
}

/*The list structure is passed in, along with the position of the % sign,
and a copy of the format

I am trying to use this to dispatch to the correct function to process the 
different data type and return the position to the main parse function in order
to process the ones after it
*/

int		parsel2(t_struct *f, int position, const char *format, va_list ap)
{
	if(format[position] == '%' && format[position])
	{
		/*Critical thing here is that we need to handle */
		if(ft_strchr("#-+ .*0123456789hljz", format[position]))
		/*modifiers(format, f, ap);*/
			modifiers();
		else if(ft_strchr(("cspdiouxXf%"), format[position]))
		{
			conversions(format[position], position, ap, f);
			bezerostruct2(f);
		}
	}
	return (position + 1);
}


void error()
{
	write(1, "You are using it wrong, re-read readme!", 39);
}


/*This function's purpose is just to count the number of double quotes in the function

int		countdoubles(char *format)
{
	int count;
	int i;
	i = 0;
	count = 0;

	while(format[i])
	{
		if(format[i] == '\"' && format[i-1] != '\\')
			count++;
		i++;
		printf("%d", i);
	}

	if (count == 2)
		return (1);
	else
		return (0);
}*/



/*Formatparsel is seperating out the % comamnds and flags into another portion
while printing out just the ""*/

int		formatparse(const char *format, t_struct *list, va_list ap)
{
	int position;

	position = 0;
	if (!format[0])
	{
		error();
		return 0;
	}
	if(!(ft_strchr(format, '%')))
		write(1, format, ft_strlen(format));
	else
	{
		/*This is the interesting part. While the format is not at an NULL
		we write until we hit an %, which we then send off to processing 
		at parsel2, which returns the new positon after all of the flags
		and things to print, which goes back into the while loop and looks
		for more*/
		while(format[position])
		{
			/*Here the bezerostruct 2 will reset everything except for the i, which is a counter for the
			numberth argument*/
			while(format[position] != '%')
				write(1, &format[position++], 1);
			if(format[position == '%'])
			{
				position = position + 1;
				while(ft_strchr("cspdiouxXf%#-+ .*0123456789hljz", format[position]))  
					position = parsel2(list, position, format, ap);
				continue;
			}
			position++;
		}
	}
	/*ft_printf("hahaha havent built this yet");*/
	return 1;
}

/*We are opening up an variatic list and setting the start to the beginning
of the pointer; and afterwards sending it to format parse which will be 
central command for the function*/

int		ft_printf(const char *format, ...)
{
	va_list ap;
	int status;
	t_struct *s;

	if (!(s = (t_struct*)malloc(sizeof(t_struct))))
		return(0);
	bezerostruct(s);
	s->format = (char *)format;
	va_start(ap, format);
	status = formatparse(format, s, ap);
	va_end(ap);
	free(s);
	return(status);
}

int		main()
{
	char c;

	c = 'B';	
	ft_printf("%#%");
}
