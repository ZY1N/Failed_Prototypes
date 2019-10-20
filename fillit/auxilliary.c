/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxilliary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 13:31:53 by yinzhang          #+#    #+#             */
/*   Updated: 2019/04/02 12:00:14 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* *piece or piece[8], may have problem
 * initalizes the tetris piece linked list
 *
 * this way of passing in piece may lead to leaks or worse
 * */

tetris *tetris_new(int *piece, char c)
{
	tetris *new;

	new = (tetris *)malloc(sizeof(tetris));
	new->piece = piece;
	new->c = c;
	new->next = NULL;
}


/*appends the new piece at the end
 *
 * this takes a int array 
 * */

tetris *append(tetris **head, int *piece, char c)
{
	tetris *hcopy;
	tetris *newpiece;

	hcopy = *head;
	while (hcopy->next != NULL)
		hcopy = hcopy->next;
	newpiece = tetris_new(piece, char c);
	hcopy->next = newpiece;
	return (*head);
}


/*might work ask somebody, dunno if free_tetris recursion will end by itself*/
tetris *free_tetris(tetris *head)
{
	tetris *hcopy;

	while (head)
	{
		hcopy = head->next;
	   	ft_memdel((void **)&head);
		head = hcopy
	}
	return (NULL);
}

/*does the same thing as append except it stitches pieces instead of taking in int array and c*/

void	ft_newlink(tetris **head, tetris *new)
{
	tetris *hcopy;
	tetris *newpiece;

	hcopy = *head;
	while (hcopy->next != NULL)
		hcopy = hcopy->next;
	newpiece = new;
	hcopy->next = newpiece;
	return (*head)
}
