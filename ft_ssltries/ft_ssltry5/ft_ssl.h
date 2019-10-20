/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:08:54 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/28 21:08:56 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./ft_printf/includes/ft_printf.h"
//#include "./ft_printf/includes/libft.h"

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"

typedef enum	s_algo
{
	MD5 = 0,
	SHA256,
	INVALID,
}				t_algo;

typedef	struct	s_flags
{
	int		p;
	int		q;
	int		r;
	int		s;
	int		tffile;
	char	*filename;
	int		fd;
	char	*text;
	char	*stdinputtext;
}				t_flags;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmpmod(const char *s1, const char *s2);
void    md5(unsigned char *s, t_flags *options);
void    printmd5(unsigned int a0, unsigned int b0, unsigned int c0, unsigned int d0, t_flags *options, unsigned char *s);
void    sha256(unsigned char *s, t_flags *options);
void printsha256(unsigned int h0, unsigned int h1, unsigned int h2, unsigned int h3, unsigned int h4, unsigned int h5, unsigned int h6, unsigned int h7, t_flags *options, unsigned char *s);
#endif
