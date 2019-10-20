/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yinzhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:07:50 by yinzhang          #+#    #+#             */
/*   Updated: 2019/07/28 21:07:52 by yinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "./ft_printf/includes/ft_printf.h"
#include "./ft_printf/includes/libft.h"

/*======================================================================*/

void	ifunknown(char *s)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\nStandard \
	commands:\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher \
	commands:\n", s);
	exit(-1);
}


/*======================================================================*/

t_algo	findalgo(char *s)
{
	if (ft_strcmp(s, "md5") == 0)
		return(MD5);
	else if (ft_strcmp(s, "sha256") == 0)
		return(SHA256);
	return(INVALID);
}

void	badflagerror()
{
	ft_printf("Accepted flags: -p -q -r -s\n");
	exit(-1);
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
}

void appendstring(char *s, char c)
{
	int	strlen = ft_strlen(s) + 1;

	printf("%c %d", c, strlen);
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



int		Add(int a, int b)
{
	return a+b;
}

void jumptable(char *input, t_flags *options, t_algo algo)
{
	void (*pmd5)(unsigned char *, t_flags *);
	pmd5 = &md5;

	void (*psha256)(unsigned char *, t_flags *);
	psha256 = &sha256;

	if (algo == MD5)
		(*pmd5)((unsigned char *)input, options); 
	else if (algo == SHA256)
		(*psha256)((unsigned char *)input, options);

}

void	findflags(char *s, t_flags *options)
{
		if (ft_strcmp("-p", s) == 0)
			options->p = 1;
		else if (ft_strcmp("-q", s) == 0)
			options->q = 1;
		else if (ft_strcmp("-r", s) == 0)
			options->r = 1;
		else if (ft_strcmp("-s", s) == 0)
			options->s = 1;			
		else if (options->s == 0)
			options->filename = s;
		else if(options->s == 1)
			options->text = s;
}

char *extractfdtext(int n)
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
	return(s);
}

void	invalidfile(t_flags *options)
{
	ft_printf("%s: No such file or directory\n", options->filename);
}


void findinput(t_flags *options)
{
	int n = 0;
	
	if(options->filename != NULL)
	{
		n = open(options->filename, O_RDONLY);

		if (n == -1)
		{
			invalidfile(options);
		}
		if (n != -1)
			options->text = extractfdtext(n);
	}

	if(options->filename == NULL)
		options->stdinputtext = extractfdtext(0);
	else if (options->p == 1)
		options->stdinputtext = extractfdtext(0);
} 




/* 
void	parseNdispatch(char *s, t_flags *options, t_algo algo)
{
	//ft_printf("%s\n", s);


	
	

	if (options->s == 0)
		options->filename = s;
	
	else if(options->s == 1)
		options->text = s; 


	ft_printf("%s\n", options->stdinputtext);
	ft_printf("%s\n", options->text);



	if (options->s == 0)
		findinput(options);


	if (options->stdinputtext != NULL)
		jumptable(options->stdinputtext, options, algo);

	if (options->p == 1 && options->filename != NULL)
		options->p = 0;

	if (options->text != NULL)
		jumptable(options->text, options, algo);
} */



int		main(int argc, char **argv)
{
	t_algo algo;
	t_flags *options;
	int		n;


	n = 0;

	options = (t_flags *)malloc(sizeof(t_flags));

	initflags(options);



	if (argc > 1)
	{

		algo = findalgo(argv[1]);

		if (algo == INVALID)
			ifunknown(argv[1]);



	// main dispatch
		while(n++ < argc - 1)
		{
			
			ft_printf("%s\n", argv[n]);

			if (ft_strcmp("-p", argv[n]) == 0)
				options->p = 1;
			else if (ft_strcmp("-q", argv[n]) == 0)
				options->q = 1;
			else if (ft_strcmp("-r", argv[n]) == 0)
				options->r = 1;
			else if (ft_strcmp("-s", argv[n]) == 0)
				options->s = 1;
			//parseNdispatch(argv[n], options, algo);
		}

/* 
		while (n++ < argc - 1)
			findflags(argv[n], options);

		

		// now we need to grab the string UNDERCONSTRUCTION



		if (options->s == 0)
			findinput(options);


		if (options->stdinputtext != NULL)
			jumptable(options->stdinputtext, options, algo);

		if (options->p == 1 && options->filename != NULL)
			options->p = 0;

		if (options->text != NULL)
			jumptable(options->text, options, algo);
*/
	}
	else 
		write(1, USAGE, 52);
}
