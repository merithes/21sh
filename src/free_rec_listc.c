/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_rec_listc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 16:47:07 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/06 17:15:43 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				free_rec_listc(t_listc *chain_to_free, int free_cont)
{
	if (!chain_to_free)
		return ;
	while (chain_to_free->prev)
		chain_to_free = chain_to_free->prev;
	while (chain_to_free)
	{
		if (free_cont & F_MAIN_ONLY)
			free(chain_to_free->cont);
		else if (free_cont & F_ALL)
			free_rec_char(chain_to_free->cont);
		chain_to_free->file ? free(chain_to_free->file) : 0;
		if (chain_to_free->next)
		{
			chain_to_free = chain_to_free->next;
			free(chain_to_free->prev);
		}
		else
		{
			free(chain_to_free);
			chain_to_free = NULL;
		}
	}
}
