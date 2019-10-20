/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 20:07:24 by yinzhang          #+#    #+#             */
/*   Updated: 2019/04/02 12:11:48 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		main(int argc, char **argv)
{
	int fd;

	if (argv < 2)
	{
		ft_putstr("usage: feed me 1");
		return (1);
	}
	else if (argv > 2)
	{
		ft_putstr("usage: you fed me too much try again");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	validation (fd);	
}

/*
 * fix data structures
 * make sure that the auxiliary functions work
 * */
