/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 14:23:57 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/06 20:56:51 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

t_listc				*create_chain_link(t_listc *prevv)
{
	t_listc			*outp;

	if (!(outp = malloc(sizeof(t_listc))))
		ft_error("Memory allocation failed.\n", -1);
	outp->prev = prevv;
	outp->next = NULL;
	outp->cont = NULL;
	outp->sep_type = 0;
	return (outp);
}

int					craft_chain(t_listc *outp, char **cli)
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

//	printf("wuta\n");
	outp = create_chain_link(NULL);
//	printf("wut\n");
	if ((err = craft_chain(outp, inp)) < 0)
	{
		free_rec_char(inp);
		free_rec_listc(outp, F_MAIN_ONLY);
//		print_parse_error(err);
//	printf("}}%p\n", outp->cont[0]);
		return (NULL);
	}
//	printf("[]%p\n", outp->cont[0]);
/*	while (outp)
	{
		printf("%d\t%s\n", outp->sep_type, outp->cont);
		outp = outp->next;
	}*/
	return (outp);
}
