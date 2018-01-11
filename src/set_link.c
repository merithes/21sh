/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 14:23:57 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/11 18:12:05 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				set_sep(t_listc *lnk, char *sep)
{
	if (!sep || !sep[0])
		lnk->sep_type = NONE;
	else if (!ft_strcmp(sep, ";"))
		lnk->sep_type = SEPA;
	else if (!ft_strcmp(sep, "|"))
		lnk->sep_type = PIPE;
	else if (!ft_strcmp(sep, "&&"))
		lnk->sep_type = AND;
	else if (!ft_strcmp(sep, "||"))
		lnk->sep_type = OR;
	else if (!ft_strcmp(sep, "&"))
		lnk->sep_type = BCKG;
}

void				set_cont(t_listc *lnk, char **cont_main, int i)
{
	char			**tmp_cont;
	int				cursor;

	cursor = -1;
	if (!(tmp_cont = malloc(sizeof(char *) * i + 1)))
		ft_error(MAF, -1);
	ft_bzero(tmp_cont, sizeof(char *) * i + 1);
	lnk->cont = tmp_cont;
	while (i > ++cursor)
		lnk->cont[cursor] = cont_main[cursor];
//	printf("-=%d:%d:%s\n]]%s\n", i, cursor, lnk->cont[0], cont_main[0]);
	lnk->cont[cursor] = NULL;
}

char				**set_link(t_listc *link, char **cli)
{
	int				i;

	i = -1;
	while (cli[++i] != NULL)
		if (!ft_strcmp(cli[i], ";") || !ft_strcmp(cli[i], "|") ||
			!ft_strcmp(cli[i], "||") || !ft_strcmp(cli[i], "&&") ||
				!ft_strcmp(cli[i], "&"))
			break ;
	set_sep(link, cli[i]);
	set_cont(link, cli, i);
//	set_redirs(link);
//	printf("<>%s\n", link->cont[0]);
//	printf("/\\%d:%s\n", i, cli[i + 1]);
	cli += i + 1;
	return (cli);
}
