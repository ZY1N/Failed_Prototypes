/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 19:25:04 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/16 19:25:05 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>


//thing that we use
unsigned char *block;

// 16 words 32 bit each
uint32_t words[16];

//blocks each int is 4 bytes or (32 bits) 4*32 = 128
static unsigned int a = 0x67452301;
static unsigned int b = 0xefcdab89;
static unsigned int c = 0x98badcfe;
static unsigned int d = 0x10325476;

//unchanged blocks og abcd
unsigned int a0 = 0x67452301;
unsigned int b0 = 0xefcdab89;
unsigned int c0 = 0x98badcfe;
unsigned int d0 = 0x10325476;

unsigned int rotTable[64];


unsigned int cTable[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7,
	12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};


/* 
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
} */

void calcrotTable(int i)
{
	//long power2to32;
	while (i < 64)
	{
		rotTable[i] = pow(2, 32) * fabs(sin(i + 1)); 
		i++;
	}
}


int     findsize(unsigned char *s)
{
    int i;
    int x;

    x = 0;
    i = 0;
    while(s[i])
        i++;
    x = ((i+8) / 64) * 64 + 64;
    return(x);
}

/* 
unsigned char	*ft_strnew(size_t size)
{
	unsigned char *t;
	unsigned char *u;

	if (!(t = (unsigned char *)malloc(size + 1)))
		return (NULL);
	u = t;
	while (size--)
		*u++ = '\0';
	*u = '\0';
	return (t);
} */

static int    blockprocessing(unsigned char *s)
{
    int sizeblocks;
    long i;
    long x;
    long y;

    x = 8;
    i = 0;

    sizeblocks = findsize(s);

    block = (unsigned char *)ft_strnew(sizeblocks); 
    while(s[i])
    {
        block[i] = s[i];
        i++;
    }
    block[i] = 1 << 7;
    y = i * 8;
   
    while (x > 0)
    {
        block[sizeblocks - x] = y >> (8 * (8 - x));
        x--;
    } 
    return(sizeblocks*8);
}

static void    loadwords(int i)
{
  int x = 0; 
  
  while (x < 16)
  {
    words[x] = 0;
    words[x] += block[(i - 1) * 64 + x * 4 + 0];
    words[x] += block[(i - 1) * 64 + x * 4 + 1] << 8;
    words[x] += block[(i - 1) * 64 + x * 4 + 2] << 16;
    words[x] += block[(i - 1) * 64 + x * 4 + 3] << 24;
    x++;
  }
}

void	mainmd5()
{
	int i = 0;
	uint32_t f = 0;
	uint32_t g;

	g = 0;
    a = a0;
    b = b0;
    c = c0;
    d = d0;
	while (i <= 63)
	{
		if (i < 16)
		{
			f = (b & c) | ((~b) & d);
			g = i;
		}
		else if (i < 32)
		{
			f = (d & b) | ((~d) & c);
			g = (5*i + 1) % 16;
		}
		else if (i < 48)
		{
			f = b ^ c ^ d;
			g = (3*i + 5) % 16;
		}
		else if (i < 64)
		{
			f = c ^ (b | (~d));
			g = (7*i) % 16;
		}
		f = f + a + rotTable[i] + words[g];
		a = d;
		d = c;
		c = b;
        b += ((f << cTable[i]) | (f >> (32 - cTable[i])));

  //      printf("\na%u\n", a);
    //    printf("\nb%u\n", b);
      //  printf("\nc%u\n", c);
       // printf("\nd%u\n", d);
        i++;
	}
	a0 = a0 + a;
	b0 = b0 + b;
	c0 = c0 + c;
	d0 = d0 + d;
}

int		reverse(int i)
{
	int new;

	new = 0;
	new += i << 24 & 0xff000000;
	new += i << 8 & 0xff0000;
	new += i >> 8 & 0xff00;
	new += i >> 24 & 0xff;
	return (new);
}

void    initconsts()
{
    a = 0x67452301;
    b = 0xefcdab89;
    c = 0x98badcfe;
    d = 0x10325476;

    //unchanged blocks og abcd
    a0 = 0x67452301;
    b0 = 0xefcdab89;
    c0 = 0x98badcfe;
    d0 = 0x10325476;    
}

void    md5(unsigned char *s, t_flags *options)
{
    int i = 1;
    int blocksize;

    initconsts();
    blocksize = blockprocessing(s);
    calcrotTable(0);

    while (blocksize/i >= 512)
    {
        loadwords(i);
        mainmd5();
        i++;
    }  

/*
    printBits(sizeof(a0), &a0);
    printBits(sizeof(a0), &b0);
    printBits(sizeof(a0), &c0);
    printBits(sizeof(a0), &d0); 

printf("%.8x %.8x %.8x %.8x", a0, b0, c0, d0); */

 a0 = reverse(a0);
  b0 = reverse(b0);
   c0 = reverse(c0);
    d0 = reverse(d0);
/* 
    printf("\n\n");

        printBits(sizeof(a0), &a0);
    printBits(sizeof(a0), &b0);
    printBits(sizeof(a0), &c0);
    printBits(sizeof(a0), &d0); */

    printmd5(a0, b0, c0, d0, options, s);

//    printf("%.8x %.8x %.8x %.8x", a0, b0, c0, d0);

}

/* 
int main(int argc, char **argv)
{
    if (argc == 2)
    {
        md5((unsigned char *)argv[1]);
    }
}*/