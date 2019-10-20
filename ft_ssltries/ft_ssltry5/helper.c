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

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}


int		ft_strcmp(const char *s1, const char *s2)
{
		int i;

		i = 0;
		while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_strcmpmod(const char *s1, const char *s2)
{
		int i;

		i = 0;
		while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
			i++;
		
		if (s1[i] == '\0' && s2[i] == '\0')
			return(1);
		else
			return(0);
}

/* 
unsigned char	*ft_strnew(size_t size)
{
	char *t;
	char *u;

	if (!(t = (char *)malloc(size + 1)))
		return (NULL);
	u = t;
	while (size--)
		*u++ = '\0';
	*u = '\0';
	return (t);
 */

/*
int	ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
} */