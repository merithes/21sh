/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_interpret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 04:06:33 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/26 22:24:57 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

int					quotes_count(char *inp)
{
	int				i;
	int				count;

	i = -1;
	count = 0;
	while (inp[++i])
	{
		if (inp[i] == '\\' && inp[i + 1] != 0)
			i++;
		else if (inp[i] == '"')
			count++;
		if (!inp[i])
			break ;
	}
	return (count);
}

char				*create_wd(char *inp, int qty)
{
	char			*outp;
	int				i;
	int				io;

	outp = ft_strnew(qty + 1);
	i = 0;
	io = 0;
	while (inp[i] && inp[i] > 32)
	{
		if (inp[i] == '\\')
			i++;
		if (inp[i] == '"' && (i == 0 || inp[i - 1] != '\\'))
			while (inp[++i] != '"')
			{
				if (inp[i] == '\\')
					i++;
				outp[io++] = inp[i];
			}
		else
			outp[io++] = inp[i];
		i++;
	}
	return (outp);
}

int					get_wd(char *inp, char **to_set)
{
	int				i;

	i = -1;
	while (inp[++i])
	{
		if (inp[i] == '\\')
			i += 2;
		else if (inp[i] == '"')
		{
			i++;
			while (inp[i] != '"')
			{
				if (inp[i] == '\\')
					i++;
				i++;
			}
		}
		if (inp[i] <= 32)
			break ;
	}
	if (i > 0)
		*to_set = create_wd(inp, i);
	return (i);
}

char				**splitter(char *inp)
{
	int				i;
	int				io;
	char			**outp;

	i = 0;
	io = 0;
	if (!(outp = malloc(sizeof(char *) * 6)))
		return (NULL);
	ft_bzero(outp, sizeof(char *) * 6);
	if ((quotes_count(inp) % 2))
	{
		ft_putstr("Invalid amout of quotes.\n");
		return (NULL);
	}
	while (inp[i])
	{
		while (inp[i] && inp[i] <= 32)
			i++;
		i += get_wd(inp + i, &(outp[io++]));
		if (!(i % 5) && i != 0)
			outp = ft_realloc(outp, sizeof(char *) * (i + 6));
	}
	outp[io] = NULL;
	return (outp);
}
