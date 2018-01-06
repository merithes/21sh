/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 14:23:57 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/06 16:43:25 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

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
	return (&cli[i])
}
