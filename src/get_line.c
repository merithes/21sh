/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:52:10 by vboivin           #+#    #+#             */
/*   Updated: 2017/12/02 23:16:35 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

char				*add_char(char buffer[6], unsigned int cursor, char *scribe)
{
	char			*tmp;
	size_t			len;

	write(1, &buffer[0], 1);
	len = ft_strlen(scribe);
	if (!(tmp = malloc(len + 2)))
		ft_error("Couldn't mallocate.\n", -1);
	ft_bzero(tmp, len + 2);
	ft_strncpy(tmp, scribe, cursor);
	tmp[cursor] = buffer[0];
	ft_strcat(tmp, scribe + cursor);
	ft_putstr(tmp + cursor + 1);
	scribe ? free(scribe) : 0;
	return (tmp);
}

int					special_check(char buffer[6], char *scribe)
{
	(void)scribe;
	if (buffer[0] == 27 || buffer[0] == 4 || buffer[0] == 12)
		return (1);
	return (0);
}

unsigned int		special_act(char buffer[6], char *scribe, int cursor)
{
	(void)scribe;
	if (buffer[0] == 27 && buffer[1] == 91)
	{
		if (buffer[2] == 67 || buffer[2] == 68)
			return (k_arrows_sides(buffer[2] - 67, cursor, scribe));
		else if (buffer[2] == 72 || buffer[2] == 70)
			return (k_home_end(buffer[2] - 70, cursor, scribe));/*
		else if (buffer[2] == 65 || buffer[2] == 66)
			return (k_arrows_histo(buffer[2] - 65), cursor);*/
		return (cursor);
	}
	return (cursor);
}
//		printf("%d\t%d\t%d\t%d\t%d\t%d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
int					get_cmdl(char **to_fill)

{
	char			buffer[6];
	char			*scribe;
	unsigned int	cursor;
	int				ret;

	ft_bzero(buffer, 6);
	cursor = 0;
	scribe = ft_strdup("");
	while ((ret = read(0, buffer, 6)) > 0)
	{
		if ((buffer[0] == 4 && !cursor && !scribe[0]) || buffer[0] == 10)
		{
			ret = (buffer[0] == 10) ? 1 : 0;
			break ;
		}
		else if ((buffer[0] == 127 && buffer[1] == 0 )|| (buffer[0] == 27
			&& buffer[1] == 91 && buffer[2] == 51 && buffer[3] == 126))
			cursor = k_del(cursor, scribe, buffer);
		else if (special_check(buffer, scribe))
			cursor = special_act(buffer, scribe, cursor);
		else
			scribe = add_char(buffer, cursor++, scribe);
		ft_bzero(buffer, 6);
	}
	*to_fill = scribe;
	return (ret);
}

int					get_line(int read_mode, char **to_fill)
{
	int				tmp;

	if (read_mode)
	{
		tmp = get_cmdl(to_fill);
		write(1, "\n", 1);
		return (tmp);
	}
	else
		return (get_next_line(0, to_fill));
}
