/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_delimiters_listing-stuff.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:39:52 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/10 17:43:33 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				append_newlink(char *inp, t_list *cursor)
{
	t_list			*outp;

	while (cursor->next)
		cursor = cursor->next;
	if (!(outp = ft_lstnew(inp, ft_strlen(inp))))
		ft_error(MAF, -1);
	cursor->next = outp;
}

int					length_until_delim(char *inp)
{
	int				i;

	i = -1;
	while (inp[++i])
	{
		if (inp[i] == '\\')
			i++;
		else if (inp[i] == '&' || inp[i] == '|' || inp[i] == ';')
		{
//			printf("returning %d because %c is a delim in %s\n", i, inp[i], inp);
			return (i);
		}
	}
	return (i);
}

int					add_delim(char *inp, t_list *cursor)
{
	if (ft_strstr(inp, "||") == inp || ft_strstr(inp, "&&") == inp)
	{
		if (ft_strstr(inp, "||") == inp)
			append_newlink("||", cursor);
		else
			append_newlink("&&", cursor);
		return (2);
	}
	if (inp[0] == ';')
		append_newlink(";", cursor);
	else if (inp[0] == '&')
		append_newlink("&", cursor);
	else if (inp[0] == '|')
		append_newlink("|", cursor);
	return (1);
}

int					add_simple_command(char *inp, t_list *cursor, int len)
{
	char			tmp[len + 1];

	ft_bzero(tmp, len + 1);
	ft_strncpy(tmp, inp, len);
//	printf("adding %s\n", tmp);
	append_newlink(tmp, cursor);
	return (len);
}

void				cut_and_stock(char *inp, t_list *cursor)
{
	int				len;
	int				i;

	i = 0;
	while (inp[i])
	{
//		printf("testing %s at %d for %s\n", inp, i, inp + i);
		if (!contains_delims(inp + i))
			i += add_simple_command(inp + i, cursor, ft_strlen(inp + i));
		else if ((len = length_until_delim(inp + i)) == 0)
		{
//			printf("delim_here:\t%s\t%d|", inp + i, i);
			i += add_delim(inp + i, cursor);
//			printf("%d\n", i);
		}
		else
			i += add_simple_command(inp + i, cursor, len);
//		printf("al\n");
	}
//	printf("out\n");
}

t_list				*convert_inp_lst(char **inp)
{
	int				i;
	t_list			outp[1];
	t_list			*cursor;

	i = -1;
	outp->next = NULL;
	cursor = outp;
	while (inp[++i] != NULL)
	{
		if (contains_delims(inp[i]))
			cut_and_stock(inp[i], cursor);
		else
			append_newlink(inp[i], cursor);
		while (cursor->next)
			cursor = cursor->next;
	}
	cursor = outp->next;
	while (cursor)
	{
//		printf("%s\n", (char *)cursor->content);
		cursor = cursor->next;
	}
//	printf("outss\n");
	return (outp->next);
}
