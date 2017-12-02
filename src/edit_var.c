/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:27:16 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/21 06:38:05 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

int					edit_var_content(t_env *elem, char *cont, int booley)
{
	int				len;

	if (!elem)
		return (-1);
	len = cont ? ft_strlen(cont) : 0;
	len += elem->name ? ft_strlen(elem->name) : 0;
	elem->full ? free(elem->full) : 1;
	if (!(elem->full = malloc(len + 2)))
		return (-1);
	booley ? free(elem->cont) : 0;
	elem->cont = cont;
	(elem->full) ? ft_bzero(elem->full, len + 2) : 0;
	(elem->full && elem->name) ? ft_strcat(elem->full, elem->name) : 0;
	(elem->full) ? ft_strncat(elem->full, "=", 1) : 0;
	(elem->full && elem->cont) ? ft_strcat(elem->full, elem->cont) : 0;
	return (0);
}

int					edit_specific_var(t_env *root, char *lf, char *newc)
{
	t_env			*cursor;

	if (!root || !lf || !newc)
		return (-1);
	if (!(cursor = get_env_var(lf, root)))
	{
		if (!(new_var(root, lf, newc, 0)))
			return (-1);
		return (1);
	}
	edit_var_content(cursor, ft_strdup(newc), 1);
	return (0);
}
