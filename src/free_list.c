/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:20:18 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/23 01:12:34 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				free_list(t_env *root)
{
	t_env			*cursor;
	t_env			*tmp;

	if (!root)
		return ;
	tmp = NULL;
	cursor = root;
	while (cursor || tmp)
	{
		tmp ? free(tmp) : 0;
		if (!cursor)
			break ;
		cursor->name ? free(cursor->name) : 0;
		cursor->cont ? free(cursor->cont) : 0;
		cursor->full ? free(cursor->full) : 0;
		tmp = cursor;
		cursor = cursor->next;
	}
}
