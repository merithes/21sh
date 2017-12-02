/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_arrows_sides.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:17:51 by vboivin           #+#    #+#             */
/*   Updated: 2017/12/02 21:28:26 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

int					k_arrows_sides(int left, unsigned int cursor, char *scribe)
{
	if (cursor == 0 && left == 1)
		return (cursor);
	if (left == 1 && cursor > 0)
	{
		write(1, "\033[1D", 4);
		return (cursor - 1);
	}
	else if (left == 0 && scribe[cursor])
	{
		write(1, "\033[1C", 4);
		return (cursor + 1);
	}
	return (cursor);
}
