/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 07:32:00 by yinzhang          #+#    #+#             */
/*   Updated: 2019/03/29 08:49:01 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*find way to generate board and grow it accodingly
 *
 * function to allocate memory for board
 * function to find size to malloc for
 * */
int		min_size(tetris *isfriend)
{
	int hashnum;
	int sqrt;

	hashnum = 0;
	while (isfriend->next != NULL)
		hashnum++;
	hashnum = hashnum * 4;
	sqrt = 1;
	while ((sqrt * sqrt) < hashnum)
		sqrt++;
	return (sqrt - 1);
}

char	**build_board(int size)
{
	unsigned int	i;
	char			**board;

	i = 0;
	board = (char**)malloc(sizeof(char*) * (size + 1));
	while (i < size)
	{
		board[i] = ft_strnew(size + 1);
		board[i] = ft_memset(board[i], '.', size);
		i++;
	}
	board[i] = 0;
	return (board);
}
