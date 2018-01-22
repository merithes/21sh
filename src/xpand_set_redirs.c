/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand_set_redirs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:57:47 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/16 19:08:59 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

t_redir				*mk_redir(void)
{
	t_redir			*outp;

	if (!(outp = malloc(sizeof(t_redir))))
		ft_error(MAF, -1);
	ft_bzero(outp->redir, sizeof(int) * 3);
	outp->file = NULL;
	next = NULL;
	return(outp);
}

void				set_redir(t_listc *inp, int i)
{
	int				len_delim;
	int				len_strin;

	if ((len_delim = ft_strlen(inp->cont[i])) == 1)
		if (!inp->cont[i + 1] || is_token(inp->cont[i]))
			return (-1);
}

int					expand_set_redirs(t_listc *inp)
{
	int				i;
	int				tmp;

	while (inp != NULL)
	{
		i = -1;
		while (inp->cont[++i])
			if ((ft_strstr(inp->cont[i], ">") || ft_strrchr(inp->cont[i], "<")))
				if ((tmp = set_redir(inp, i)) < 0)
					return (print_errors_redir(inp, i, tmp));
		inp = inp->next;
	}
}
