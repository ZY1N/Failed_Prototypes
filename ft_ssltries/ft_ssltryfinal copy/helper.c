/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:17:00 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/28 21:17:01 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*extractfdtext(int n)
{
	char *s;
	char *c;

	s = ft_strnew(0);
	c = ft_strnew(1);
	while (read(n, c, 1) != 0)
	{
		s = ld_stradd(s, c);
		c = ft_strnew(1);
	}
	free(c);
	return (s);
}

char	*ld_stradd(char *a, char *b)
{
	char	*new;
	size_t	i;

	i = 0;
	new = ft_strnew(ft_strlen(a) + ft_strlen(b));
	while (i < ft_strlen(a) + ft_strlen(b))
	{
		if (i < ft_strlen(a))
		{
			new[i] = a[i];
		}
		else
		{
			new[i] = b[i - ft_strlen(a)];
		}
		i++;
	}
	free(a);
	free(b);
	return (new);
}

void	initflags(t_flags *options)
{
	options->p = 0;
	options->q = 0;
	options->r = 0;
	options->s = 0;
	options->filename = NULL;
	options->fd = 0;
	options->text = NULL;
	options->stdinputtext = NULL;
	options->textwithsflag = NULL;
	options->emptytext = NULL;
}

t_algo	findalgo(char *s)
{
	if (ft_strcmp(s, "md5") == 0)
		return (MD5);
	else if (ft_strcmp(s, "sha256") == 0)
		return (SHA256);
	return (INVALID);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
