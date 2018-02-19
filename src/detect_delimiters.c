/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_delimiters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:38:52 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/22 17:59:25 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

int					contains_delims(char *inp)
{
	if (!ft_strcmp(inp, "&&") || !ft_strcmp(inp, "||") ||
		!ft_strcmp(inp, ";") || !ft_strcmp(inp, "|") || !ft_strcmp(inp, "&"))
		return (0);
	while (*inp)
	{
		if (*inp == '\\')
			inp++;
		else if (*inp == '|' || *inp == ';')
			return (1);
		else
			inp++;
	}
	return (0);
}

int					check_separators_bigscale(char **inp)
{
	int				i;

	i = -1;
	while (inp[++i])
	{
		if (contains_delims(inp[i]))
			return (1);
		else if (contains_bad_redirs(inp[i]))
			return (1);
	}
	return (0);
}

char				**recompress_lst(t_list *lst)
{
	char			**outp;
	int				len;
	t_list			*cursor;
	t_list			*tmp;

	len = 0;
	cursor = lst;
	while (cursor->next)
	{
		cursor = cursor->next;
		len++;
	}
	if (!(outp = malloc(sizeof(char *) * (len + 2))))
		ft_error(MAF, -1);
	ft_bzero(outp, sizeof(char *) * (len + 2));
	cursor = lst;
	len = -1;
	while (cursor)
	{
		outp[++len] = (char *)cursor->content;
		tmp = cursor;
		cursor = cursor->next;
		tmp ? free(tmp) : 0;
	}
	outp[len + 1] = 0;
	return (outp);
}

int serf = 0;

char				**detect_bad_delimiters(char **inp)
{
	t_list			*list;
	char			**outp;

	if (!inp || !check_separators_bigscale(inp))
		return (inp);
	list = convert_inp_lst(inp);
	list = check_redirs(list);
	outp = recompress_lst(list);
	int i; i = -1; while (outp[++i])printf("%p :: |%s|\n", outp[i], outp[i]);
//	sleep(50);
//free_rec_char(*inp);
	return (outp);
}

int					detect_delimiters(char **inp)
{
	int				i;

	i = -1;
	while (inp[++i] != NULL)
	{
		if (!ft_strcmp("|", inp[i]))
			return (1);
		else if (!ft_strcmp(";", inp[i]))
			return (1);
		else if (!ft_strcmp("&", inp[i]))
			return (1);
		else if (!ft_strcmp("||", inp[i]))
			return (1);
		else if (!ft_strcmp("&&", inp[i]))
			return (1);
	}
	return (0);
}
