/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 12:56:44 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/25 12:56:46 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ft_ssl.h"

//these are the intial hash values, 32, fractional parts of squre roots of first 8 primes
// also 32 * 8 = 256 
unsigned int h0 = 0x6a09e667;
unsigned int h1 = 0xbb67ae85;
unsigned int h2 = 0x3c6ef372;
unsigned int h3 = 0xa54ff53a;
unsigned int h4 = 0x510e527f;
unsigned int h5 = 0x9b05688c;
unsigned int h6 = 0x1f83d9ab;
unsigned int h7 = 0x5be0cd19;

// these will  hold the other versions
unsigned int a = 0x6a09e667;
unsigned int b = 0xbb67ae85;
unsigned int c = 0x3c6ef372;
unsigned int d = 0xa54ff53a;
unsigned int e = 0x510e527f;
unsigned int f = 0x9b05688c;
unsigned int g = 0x1f83d9ab;
unsigned int h = 0x5be0cd19;


//intinalize of round constants

unsigned int k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

//thing that we need
unsigned char *block;

// the words
uint32_t words[64];




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
}


unsigned int    findblocksize(unsigned char *s)
{
    int i = 0;
  //  int z = 0;

    while (s[i])
        i++;

    while (i % 55 != 0)
        i++;
    i = i * 8;

    return (i + (i/440) * 72);
}

void    block_bezero(unsigned int blocksize)
{
    unsigned int i = 0;

    while (i < blocksize)
    {
        block[i] = '\0';

        i++;
    }
}

char	*ft_strcpy(char *dst, const char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/* *
unsigned int    ft_strlen(char *s)
{
    unsigned int i = 0;

    while(s[i])
        i++;
    return(i);
} */

void    blockprocessing(unsigned int blocksize, unsigned char *s)
{
  //  int i = 0;
    unsigned int strlen = ft_strlen((const char *)s);
    long length64;

    block = (unsigned char *)malloc(blocksize);
    block_bezero(blocksize); 

/*
    while (i < 64)
    {
        printBits(sizeof(block[i]), &block[i]);
        i++;
    }  */

  //  printf("\n");

    block = (unsigned char *)ft_strcpy((char *)block, (const char *)s);

    // come back to the padding
    block[strlen] = 128;


    length64 = strlen * 8;

   // printBits(sizeof(length64), &length64);

   // printf("blocksize %d", blocksize);
   // printf("\n\n");
    block[blocksize - 1] = (length64); //| (length64 << 32);

    



    /* 
    i = 0;
    while (i < 64)
    {
        printBits(sizeof(block[i]), &block[i]);
        i++;
    } */     

}

uint32_t rightrot(uint32_t word, int n)
{
    word = (word >> n) | (word << (32 - n));
    return(word);
}


void    bigendianmemcopy(uint32_t *wordz)
{
    int x  = 0;
    int y = 0;
    int z = 0;

    while (x < 16)
    {
        y = 0;
        while (y < 4)
        {
            wordz[x] = wordz[x] << 8 | block[z];
            //wordz[x] = wordz[x] << 8;
            //printBits(sizeof(wordz[x]), &wordz[x]);
            z++;
            y++;
        }
//        printBits(sizeof(src2[x]), &src[x]);
        x++;
    }


/*
    x = 0;
    int i = 0;

    while (n > 0)
    {
        dst2[i] = src2[n - 1];


        printBits(sizeof(src2[n - 1]), &dst2[n - 1]);
        i++;
        n--;
    } */
   // return(dst2);
}

uint32_t *   loadwords()
{
    int i = 16;
    uint32_t s0;
    uint32_t s1;
    /* 
    while (i < 64)
    {
        printBits(sizeof(block[i]), &block[i]);
        printf("\n");
        i++;
    }
    */

    uint32_t *wordz = malloc(sizeof(uint32_t) * 64);



    //wordz = (uint32_t *)block;

    bigendianmemcopy(wordz);


   //bezeros the whole thing
    
    /* 
    int z = 16;
    while (z < 64)
    {
        wordz[z] = '\0';
        z++;
    } */

    while (i < 64)
    {
       s0 = rightrot(wordz[i - 15], 7) ^ rightrot(wordz[i - 15], 18) ^ (wordz[i - 15] >> 3);
       s1 = rightrot(wordz[i - 2], 17) ^ rightrot(wordz[i - 2], 19) ^ (wordz[i - 2] >> 10);
       wordz[i] = wordz[i - 16] + s0 + wordz[i - 7] + s1;
       i++;
    }
 
 /* 
   i = 0;
   while (i <= 64)
   {
        printBits(sizeof(wordz[i]), &wordz[i]);
        i++;
   } */
   return (wordz);
}

void    sha256algo(uint32_t *wordz)
{
    int i = 0;
    uint32_t S1;
    uint32_t ch;
    uint32_t temp1;
    uint32_t S0;
    uint32_t maj;
    uint32_t temp2;

    while (i < 64)
    {
        S1 = rightrot(e, 6) ^ rightrot(e, 11) ^ rightrot(e, 25);
        ch = (e & f) ^ ((~ e) & g);
        temp1 = h + S1 + ch + k[i] + wordz[i];
        S0 = rightrot(a, 2) ^ rightrot(a, 13) ^ rightrot(a, 22);
        maj = (a & b) ^ (a & c) ^ (b & c);
        temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
        i++;
    }
    h0 = h0 + a;
    h1 = h1 + b;
    h2 = h2 + c;
    h3 = h3 + d;
    h4 = h4 + e;
    h5 = h5 + f;
    h6 = h6 + g;
    h7 = h7 + h;
}


void    sha256(unsigned char *s, t_flags *options)
{
    unsigned int i = 0;
    unsigned int blocksize;
    uint32_t *wordz;

    blocksize = findblocksize(s);
    blockprocessing(blocksize/8, s);

    while (blocksize/512 > i)
    {
        wordz = loadwords();
        sha256algo(wordz);
        i++;
    }
    //options->p = 1;
    printsha256(h0, h1, h2, h3, h4, h5, h6, h7, options, s);
    //printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x", h0, h1, h2, h3, h4, h5, h6, h7);

}

/* 

int     main(int argc, char **argv)
{
  //  int i = 0;

    if (argc == 2)
    {
        sha256(argv[1]);
    }
} */   