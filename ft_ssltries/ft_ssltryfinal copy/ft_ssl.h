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
#include "./ft_printf/includes/libft.h"
#include <limits.h>
#include <math.h>

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
	char	*textwithsflag;
	char	*stdinputtext;
	char	*emptytext;
}				t_flags;

typedef	struct	s_md5
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;

	unsigned int a0;
	unsigned int b0;
	unsigned int c0;
	unsigned int d0;
}	t_md5;

typedef	struct s_sha256
{
	unsigned int h0;
	unsigned int h1;
	unsigned int h2;
	unsigned int h3;
	unsigned int h4;
	unsigned int h5;
	unsigned int h6;
	unsigned int h7;

	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
	unsigned int e;
	unsigned int f;
	unsigned int g;
	unsigned int h;
	int	count;
}	t_sha256;

int				findsize(unsigned char *s);
int		reverse(int i);
void			initconsts(t_md5 *md5);
void    setvar(t_md5 *md5);
void    findmessagedigest(t_md5 *md5);

unsigned int	findblocksize(unsigned char *s);
uint32_t		rrot(uint32_t wrd, int n);
void			initvariables(t_sha256 *sha2);
void			block_bezero(unsigned int blocksize, unsigned char *g_block);
//void			bigendianmemcopy(uint32_t *wrd, unsigned char *g_block);

int			bigendianmemcopy(uint32_t *wrd, unsigned char *g_block, int z);


char	*ft_strcpy(char *dst, const char *src);
char	*extractfdtext(int n);
t_algo	findalgo(char *s);
void	initflags(t_flags *options);
char	*ld_stradd(char *a, char *b);
void	ifunknown(char *s);
void	badflagerror(void);
void	invalidfile(char *s, t_algo algo);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmpmod(const char *s1, const char *s2);
void    md5(unsigned char *s, t_flags *options);
void	printmd5(t_md5 *md5, t_flags *opt, unsigned char *s);
void	printsha256(t_sha256 *sha2,t_flags *opt, unsigned char *s);

void    sha256(unsigned char *s, t_flags *options);
#endif
