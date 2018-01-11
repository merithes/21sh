/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 14:23:57 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/11 15:16:52 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

t_listc				*create_chain_link(t_listc *prevv)
{
	t_listc			*outp;

	if (!(outp = malloc(sizeof(t_listc))))
		ft_error(MAF, -1);
	outp->prev = prevv;
	outp->next = NULL;
	outp->cont = NULL;
	outp->sep_type = 0;
	return (outp);
}

int					forge_chain(t_listc *outp, char **cli)
{
	int				err;
	t_listc			*tmp;

	tmp = outp;
	err = 0;
	while (1)
	{
		cli = set_link(outp, cli);
		if (outp->sep_type == NONE)
			break ;
		else
			outp->next = create_chain_link(outp);
		outp = outp->next;
	}
//	check_parsed(save);
	return (err);
}

t_listc				*cut_string_delimiters(char **inp)
{
	t_listc			*outp;
	int				err;

	outp = create_chain_link(NULL);
	if ((err = forge_chain(outp, inp)) < 0)
	{
		free_rec_char(inp);
		free_rec_listc(outp, F_MAIN_ONLY);
//		print_parse_error(err);
		return (NULL);
	}
	return (outp);
}
