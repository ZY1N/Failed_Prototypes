/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 16:24:23 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/14 17:45:44 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdint.h>

unsigned int rotTable[64];
int	cTable[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7,
	12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
char block[55];
//need padding, maximum of 447 
char padding[447];
//need 64 representation of size
char size[8];
//blocks each int is 4 bytes or (32 bits) 4*32 = 128
unsigned int a = 0x67452301;
unsigned int b = 0xefcdab89;
unsigned int c = 0x98badcfe;
unsigned int d = 0x10325476;
//unchanged blocks og abcd
unsigned int a0 = 0x67452301;
unsigned int b0 = 0xefcdab89;
unsigned int c0 = 0x98badcfe;
unsigned int d0 = 0x10325476;

//the digest
char digest[16];

//the 512 bits broken into 16 32 bit words;
uint32_t m[16];



int		ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return(i);
}

float	ft_abs(float i)
{
	if (i < 1)
		return(i * -1);
	else
		return (i);
}

void calcrotTable(int i)
{
	long power2to32;
	while (i < 64)
	{
		rotTable[i] = pow(2, 32) * fabs(sin(i + 1)); 
		i++;
	}
}

//=============================================================//

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

uint32_t	leftrotate(uint32_t x, unsigned int c)
{
	return  ((x << c) | (x >> (32 - c)));
}


void	steps()
{
	int i = 0;
	uint32_t f;
	uint32_t g;

	g = 0;
	while (0 <= i && i <= 63)
	{
		if (0 <= i && i <= 15)
		{
			//something = (b and c) or ((not b) and D)
			f = (b & c) | ((~b) & d);
			//printBits(sizeof(f), &f);
			g = i;
		}
		else if (16 <= i && i <= 31)
		{
			//f = (B and C) or ((not D) and C)
			f = (b & c) | ((~d) & c);
			g = (5*i + 1) % 16;
		}
		else if (32 <= i && i <= 47)
		{
			// f = b xor c xor d
			f = b ^ c ^ d;
			g = (3*i + 5) % 16;
		}
		else if (48 <= i && i <= 63)
		{
			// f = c xor (b or (not d))
			f = c ^ (b | (~d));
			g = (7*i) % 16;
		}
		i++;
		//the uint f add to a add to constant(cTable[i]) and add in m[g], which is the message broken up into 16 32 bit words.
		f = f + a + cTable[i] + m[g]; //this portion is when you add the the 
		a = d;
		d = c;
		c = b;
		b = b + leftrotate(f, rotTable[i]);

//		printf("a: %u\n", a);
//		printf("b: %u\n", b);	
//		printf("c: %u\n", c);
//		printf("d: %u\n", d);
	}
	a0 = a0 + a;
	b0 = b0 + b;
	c0 = c0 + c;
	d0 = d0 + d;

	//digest = a0 append to b0 c0 and d0
}

//=============================================================//

long	findlength(char *s)
{
	long i = 0;

	while(s[i])
		i++;
	return(i*8);
}

void	fillin(int word, char *s, long number64)
{
	int i = 0;
	int words = 0;
//	int wordcount = 1;

	while (s[i])
	{
		m[words] = m[words] | s[i];
		printBits(sizeof(s[i]), &s[i]);
//		printBits(sizeof(m[words]), &m[words]);
		if ((i+1)%4 == 0)
		{
			words++;
		}
//		else 
//			m[words] = m[words] << 8;
		i++;
	}

//		printf("\n[value of i %d]\n", i);

//		printf("this is the 1st");
//		printBits(sizeof(m[0]), &m[0]);
//		printf("this is the 1st");
//		printBits(sizeof(m[1]), &m[1]);
//		printf("this is the 1st");
//		printBits(sizeof(m[2]), &m[2]);

}

void	putin64(long number64)
{
//	printBits(sizeof(number64), &number64);
	m[15] = number64;
	m[14] = number64 >> 32;
//	printBits(sizeof(m[14]), &m[14]);		
//	printBits(sizeof(m[15]), &m[15]);
	//m[15]
}


void	md5(char *s)
{
	//first we need to only do 448 at a time
	//which is 55 chars
	int i;
	int slen;
	long number64;

//number64 is the size of the message in bits (char * 8)
	number64 = findlength(s);


//	printBits(sizeof(char)* 3, &s);
//	printf("\n%ld\n", number64);
//	printBits(sizeof(number64), &number64);



//start testing for filling in the message words
	fillin(0, s, number64);

	//put in the 64 bit number representation
	putin64(number64);
//end

	int z = 0;

  while (z <= 15)
	{
		printBits(sizeof(m[z]), &m[z]);
		z++;
	}


	i = 0;
	slen = ft_strlen(s);

/*
	while (i < 55 && i < slen)
	{
		block[i] = s[i];
		printf("%c", s[i]);
		i++;
	}*/


	calcrotTable(0);
	steps();
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		md5(argv[1]);
	}
}
