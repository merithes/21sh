/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 14:23:57 by vboivin           #+#    #+#             */
/*   Updated: 2018/03/16 15:08:29 by jamerlin         ###   ########.fr       */
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
	outp->status = 0;
	outp->nb_arg = 1;
	outp->redirs = NULL;
	outp->sep_type = 0;
	return (outp);
}

int					forge_chain(t_listc *outp, char **cli)
{
	int				err;
//	t_listc			*tmp;

//	tmp = outp;
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
		free_rec_listc(outp, F_ALL);
		return (NULL);
	}
//	t_listc *cpy = outp; for (int j = 0; cpy; j++){for (int i = 0; cpy->cont[i]; i++){ printf("arg[%d] = [%s]\n",j, cpy->cont[i]);}cpy = cpy->next;}
	return (outp);
}
