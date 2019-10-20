/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:04:56 by yinzhang          #+#    #+#             */
/*   Updated: 2019/04/02 13:33:58 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>


size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


/*count the number of touches 
 * cycles through the string looking for hashtags, after finding the hashtags then 
 * filters them out to see if they have one ahead behind or 5 in front or behind
 * that is counted as a touchii and if touchii is 6 or 8 then it is a valid piece
 * returns 0 and if not it returns 0
 * numbers need to be updated
 */

int touches(char *s)
{
	int i;
	int touchii;

	i= 0;
	touchii = 0;
	while (s[i])
	{
		if (s[i] == '#')
		{
			if (i < 20 && s[i + 1] == '#')
				touchii++;
			if (i > 0 && s[i - 1] == '#')
				touchii++;
			if (i <= 14 && s[i + 5] == '#')
				touchii++;
			if (i <= 5 && s[i - 5] == '#')
				touchii++;
		}
		i++;
	}
	if (touchii == 6 || touchii == 8)
		return (1);
	else
		return (0);
}

/*=================================================================*/

/*look at string s to see if it is filled with '.' and '#'
 *
 * allows first pass through of all . # and \n.
 * then if any other position besides 5 10 15 20 21 have a \n return 2
 *keeps track of numer of hash tags and if == 4 then returns 0
 * */

int		validsymbol(char *buff)
{
	int i;
	int hashtagnum;
	int dots;


	i = 0;
	hashtagnum = 0;
	dots = 0;

	while (i < ft_strlen(buff))
	{
		if (buff[i] != '.' || buff[i] != '#' || buff[i] != '\n')
			return (0);
		if ((i == 5 || i == 10 || i == 15 || i == 20 || i == 21) && buff[i] != '\n')
			return (0);
		if (buff[i] == '.')
				dots++;
		if (buff[i] == '#')
			hashtagnum++;
		i++;
	}
	if (hashtagnum == 4 && (dots + hashtagnum == 16))
		return (1);
	return (0);
}

/*==================================================================*/

/* check to see if have 4 hash tags, is 21 char or 20, is all # and ., if touching parts is 6 or 8
 * warnings:
 * 		check to see if it is working casue we are passing ssize_t into char*/

int		isvalidpiece(char *buff)
{
	if (validsymbol(buff) != 0 && touches(buff) != 0)
		return (0);
	else
		return (1);
}

/*===============================================================*/
int	*extractpiece(char *buff)
{
	int i;
	int x;
	int y;
	int pointnbr;
	static int array[8];
	int counter;

	i = 0;
	x = 0;
	y = 0;
	pointnbr = 0;
	counter = 0;
	while (buff[i])
	{
		if (pointnbr++ < 4 && counter < 8 && buff[i] == '#')
		{
			y = i / 5;
			x = i - (y * 5);
			array[counter] = x;
			counter++;
			array[counter] = y;
			counter++;
		}
		i++;
	}
	return (array);
}

int main()
{
	int *array;
	char *buff = ".#..\n###.\n....\n....\n\n";
	int i = 0;

	array = extractpiece(buff);

	while (i < 8)
	{
		printf("%d", array[i]);
		i++;
	}
}

/*===============================================================*/

/*supposed to take in a fd descriptor and then rip out 21 chars into a buffer for processing and then validation
 * might not be int be careful
 * i might need to be initialized
 * isvalid piece should return 0 if everything checks out, now we need to somehow store the buff into
 * a structure to process later 
 * */

/*

int		validation (int fd)
{
	ssize_t *buff;
	int i;
	char letter;
	tetris *tlink;
	tetris *head;

	i = 0;
	head = NULL;
	letter = 'A';
	buff = ft_newstr(21);
	while ((i = read(fd, buff, 21))  > 20)
	{
		if (isvalidpiece(buff) != 0 || (tlink = extractpiece(buff, letter++)) == NULL)
		{
			ft_memdel((void **)&buff);
			return (free_tetris(&tlink);
		}
		ft_newlink(&head, tlink);
		*ft_memdel((void **)&tlink);
	}
	ft_memdel((void **)&buff);
	if (i != 0)
		return (free_tetris);
	return (head);
}
*/
