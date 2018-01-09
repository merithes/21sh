/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_delimiters_listing-stuff.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:39:52 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/09 19:31:26 by vboivin          ###   ########.fr       */
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
			return (i);
	}
	return (i);
}

int					add_delim(char *inp, t_list *cursor)
{
	if (ft_strstr(inp, "||") == inp || ft_strstr(inp, "&&") == inp)
	{
		if (ft_strstr(inp, "||"))
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
	append_newlink(tmp, cursor);
	return (len);
}

void				cut_and_stock(char *inp, t_list *cursor)
{
	int				len;
	int				i;

	i = -1;
	while (inp[++i])
	{
		if (!contains_delims(inp + i))
			break ;
		if ((len = length_until_delim(inp)) == 0)
			i += add_delim(inp + i, cursor);
		else
			i += add_simple_command(inp + i, cursor, len);
	}
}

t_list				*convert_inp_lst(char **inp)
{
	int				i;
	t_list			*outp;
	t_list			*cursor;

	i = -1;
	if (!(outp = ft_lstnew(NULL, 0)))
		ft_error(MAF, -1);
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
	return (outp);
}
