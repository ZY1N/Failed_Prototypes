/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 19:14:29 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/30 19:14:30 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void    printmd5(unsigned int a0, unsigned int b0, unsigned int c0, unsigned int d0, t_flags *options, unsigned char *s)
{
   // ft_printf("[%s]\n", s);



    //get rid of filename == null for filename to work with p flag
    if (options->p == 1 )
        ft_printf("%s", s);

    if (options->filename != NULL && options->r == 0 && options->q == 0 && options->p == 0)
    {
        ft_printf("MD5 (%s) = ", options->filename);
    }

    if (options->s == 1 && options->q != 1 && options->r != 1)
    {
        //if (options->textwithsflag != NULL )
            ft_printf("MD5 (\"%s\") = ", options->textwithsflag); 
      //  else
            //ft_printf("MD5 (\"%s\") = ", options->emptytext); 
    }

    ft_printf("%.8x%.8x%.8x%.8x", a0, b0, c0, d0);

    if (options->s == 1 && options->q != 1 && options->r == 1)
    {
        //if (options->textwithsflag != NULL )
            ft_printf(" \"%s\"", options->textwithsflag); 
      //  else
            //ft_printf("MD5 (\"%s\") = ", options->emptytext); 
    }


    if (options->r == 1 && options->q == 0 && options->filename != NULL && options->p == 0)
        ft_printf(" %s", options->filename);
    ft_printf("\n");
    
    if (options->p == 1 )
        options->p = 2;
    
    //ft_printf("\n%d %d %d %d\n", options->p, options->q, options->r, options->s);
    options->text = NULL;
    options->textwithsflag = NULL;
    options->stdinputtext = NULL;
  //  options->filename = NULL;
}

void printsha256(unsigned int h0, unsigned int h1, unsigned int h2, unsigned int h3, unsigned int h4, unsigned int h5, unsigned int h6, unsigned int h7, t_flags *options, unsigned char *s)
{
    if (options->p == 1 )
        ft_printf("%s", s);

    if (options->filename != NULL && options->r == 0 && options->q == 0 && options->p == 0)
    {
            ft_printf("SHA256 (%s) = ", options->filename);
    }

    if (options->s)
    {
       ft_printf("sha256 (\"%s\") = ", options->textwithsflag); 
    }

    ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x", h0, h1, h2, h3, h4, h5, h6, h7);

    if (options->r == 1 && options->q == 0 && options->filename != NULL && options->p == 0)
        ft_printf(" %s", options->filename);
    
    //if (options->p == 1)
        //options->p == 0;

    ft_printf("\n");
}