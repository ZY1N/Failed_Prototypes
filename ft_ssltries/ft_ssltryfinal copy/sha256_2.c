/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:05:49 by yinzhang          #+#    #+#             */
/*   Updated: 2019/08/04 20:05:51 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	findblocksize(unsigned char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	while (i % 55 != 0)
		i++;
	i = i * 8;
	return (i + (i / 440) * 72);
}

uint32_t		rrot(uint32_t wrd, int n)
{
	wrd = (wrd >> n) | (wrd << (32 - n));
	return (wrd);
}

void			initvariables(t_sha256 *sha2)
{
	sha2->h0 = 0x6a09e667;
	sha2->h1 = 0xbb67ae85;
	sha2->h2 = 0x3c6ef372;
	sha2->h3 = 0xa54ff53a;
	sha2->h4 = 0x510e527f;
	sha2->h5 = 0x9b05688c;
	sha2->h6 = 0x1f83d9ab;
	sha2->h7 = 0x5be0cd19;
	sha2->a = 0x6a09e667;
	sha2->b = 0xbb67ae85;
	sha2->c = 0x3c6ef372;
	sha2->d = 0xa54ff53a;
	sha2->e = 0x510e527f;
	sha2->f = 0x9b05688c;
	sha2->g = 0x1f83d9ab;
	sha2->h = 0x5be0cd19;
	sha2->count = 0;
}

void			block_bezero(unsigned int blocksize, unsigned char *g_block)
{
	unsigned int i;

	i = 0;
	while (i < blocksize)
	{
		g_block[i] = '\0';
		i++;
	}
}

void printBits2(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            ft_printf("%u", byte);
        }
    }
    puts("");
}

int			bigendianmemcopy(uint32_t *wrd, unsigned char *g_block, int z)
{
	int x;
	int y;
	//int z;

	x = 0;
	y = 0;
	//z = 0;
	while (x < 16)
	{
		y = 0;
		while (y < 4)
		{
			wrd[x] = wrd[x] << 8 | g_block[z];
			z++;
			y++;
		}
		//ft_printf("\n%d\n", z);
		printBits2(sizeof(wrd[x]), &wrd[x]);
		x++;
	}
	ft_printf("\n\n");
	return(z);
}
