/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ferror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:42:21 by vboivin           #+#    #+#             */
/*   Updated: 2017/12/02 18:52:59 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

static unsigned int	k_backdel(unsigned int cursor, char *scribe)
{
	int				i;

	i = -1;
	while (scribe[++i + cursor])
		scribe[i + cursor - 1] = scribe[i + cursor];
	scribe[i + cursor - 1] = 0;
	write(1, "\033[1D", 4);
	ft_putstr(scribe + cursor - 1);
	ft_putchar(' ');
	write(1, "\033[", 2);
	ft_putnbr((int)ft_strlen(scribe) - cursor + 2);
	write(1, "D", 1);
	return (cursor - 1);
}

static unsigned int	k_currdel(unsigned int cursor, char *scribe)
{
	int				i;

	i = -1;
	while (scribe[++i + cursor + 1])
		scribe[i + cursor] = scribe[i + cursor + 1];
	scribe[i + cursor] = 0;
	ft_putstr(scribe + cursor);
	ft_putchar(' ');
	write(1, "\033[", 2);
	ft_putnbr((int)ft_strlen(scribe) - cursor + 1);
	write(1, "D", 1);
	return (cursor);
}

int					k_del(unsigned int cursor, char *scribe, char buffer[6])
{
	if (cursor == 0 && buffer[0] == 127)
		return (cursor);
	else if (cursor != 0 && buffer[0] == 127)
		return (k_backdel(cursor, scribe));
	else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51 &&
			buffer[3] == 126 && buffer[4] == 0)
		return (k_currdel(cursor, scribe));
	return (cursor);
}
