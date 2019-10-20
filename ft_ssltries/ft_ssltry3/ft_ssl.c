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
	options->textwithsflag = NULL;
	options->emptytext = NULL;
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

void	invalidfile(char *s, t_algo algo)
{
	if (algo == MD5)
		ft_printf("ft_ssl: md5: %s: No such file or directory\n", s);
	else 
		ft_printf("ft_ssl: sha256: %s: No such file or directory\n", s);
}


void findinput(t_flags *options, t_algo algo)
{
	int n = 0;



	
	if(options->filename != NULL && options->text == NULL)
	{
		n = open(options->filename, O_RDONLY);

		if (n == -1)
		{
			invalidfile(options->filename, algo);
		}
		if (n != -1)
			options->text = extractfdtext(n);
	}
	//if (options->text == NULL && options->textwithsflag == NULL && options->stdinputtext == NULL)
	
//	ft_printf("\n[%s]\n", options->emptytext);

	if(options->filename == NULL && options->stdinputtext == NULL && options->text == NULL && options->textwithsflag == NULL && options->p == 0 && options->s == 0)
		options->emptytext = extractfdtext(0);
//	else if (options->p == 1 && options->stdinputtext == NULL)
//		options->stdinputtext = extractfdtext(0);
//		ft_printf("\n[%s]\n", options->emptytext);
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

void	findflags(char *s, t_flags *options, t_algo algo)
{
//	ft_printf("%s \n\n", s);


		if (ft_strcmp("-p", s) == 0)
		{
			options->p = 1;
			options->stdinputtext = extractfdtext(0);
			jumptable(options->stdinputtext, options, algo);
			//ft_printf("%s\n", options->stdinputtext);
			
		}
		else if (ft_strcmp("-q", s) == 0)
			options->q = 1;
		else if (ft_strcmp("-r", s) == 0)
			options->r = 1;
		else if (ft_strcmp("-s", s) == 0)
		{
			if (options->s == 0)
				options->s = 1;
			else
				invalidfile(s, algo);
		}
//		else if (options->s == 0 )
//			options->filename = s;
		else if(options->s == 1 && options->textwithsflag == NULL)
		{
			options->textwithsflag = s;
			//		if(options->textwithsflag != NULL)
			jumptable(options->textwithsflag, options, algo);
			options->s = 2;
					if (options->s != 1)
			findinput(options, algo);

		if (options->emptytext != NULL)
			jumptable(options->emptytext, options, algo);

		if (options->p == 2 && options->filename != NULL)
			options->p = 0;
		if (options->text != NULL)
			jumptable(options->text, options, algo);
		}
		else
		{
			options->filename = s;
		if (options->s != 1)
			findinput(options, algo);

		if (options->emptytext != NULL)
			jumptable(options->emptytext, options, algo);

		if (options->p == 2 && options->filename != NULL)
			options->p = 0;
		if (options->text != NULL)
			jumptable(options->text, options, algo);
//			findinput(options);
		}


}



int		main(int argc, char **argv)
{
	t_algo algo;
	t_flags *options;
	int		n;
	//char *input;


	n = 1;

	options = (t_flags *)malloc(sizeof(t_flags));

	initflags(options);



	if (argc > 1)
	{

		algo = findalgo(argv[1]);

		if (algo == INVALID)
			ifunknown(argv[1]);


		while (n++ < argc - 1)
			findflags(argv[n], options, algo);

		

		// now we need to grab the string UNDERCONSTRUCTION
//		ft_printf("text: %s\n", options->text);
//		ft_printf("textwithsflag: %s\n", options->textwithsflag);
//		ft_printf("stdinputtext: %s\n", options->stdinputtext);
//		ft_printf("\n[%s]\n", options->emptytext);
//		ft_printf("\ns flag [%d]\n", options->s);
//		ft_printf("filename %s\n", options->filename);


//		if (options->text == NULL && options->textwithsflag == NULL && options->stdinputtext == NULL)
//		findinput(options);


//		ft_printf("break here\n");	

		//if (options->s != 1) 


//		ft_printf("text: %s\n", options->text);
//		ft_printf("textwithsflag: %s\n", options->textwithsflag);
//		ft_printf("stdinputtext: %s\n", options->stdinputtext);


//		ft_printf("break here\n");	



//		if (input == NULL)
			//return (-1);
		//options->text = input;


		//LOOKUP HOW TO MAKE TRUE JUMP TABLE

//		ft_printf("\nstdinput %s\n", options->stdinputtext);
//		ft_printf("\n[text %s]\n", options->text);


		//ft_printf("\n\nhere\n\n");

//		ft_printf("\n[%s]\n", options->emptytext);





		if (options->s == 0)
			findinput(options, algo);

		if (options->emptytext != NULL)
			jumptable(options->emptytext, options, algo);

//		if (options->p == 2 && options->filename != NULL)
//			options->p = 0;
//		if (options->text != NULL)
//			jumptable(options->text, options, algo);


		//if (options->s == 0)
			//free(input); 
	}
	else 
		write(1, USAGE, 52);
}
