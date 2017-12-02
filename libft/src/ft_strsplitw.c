/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <vboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 18:20:54 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/21 05:41:55 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_nb_word(const char *s)
{
	size_t	i;
	int		isword;

	i = 0;
	isword = 0;
	while (*s)
	{
		if (isword == 0 && *s > 32)
		{
			isword = 1;
			i++;
		}
		else if (isword == 1 && *s <= 32)
			isword = 0;
		s++;
	}
	return (i);
}

static size_t	ft_length_word(const char *s)
{
	size_t	length;

	length = 0;
	while (*s && *s > 32)
	{
		length++;
		s++;
	}
	return (length);
}

char			**ft_strsplitw(const char *s)
{
	char	**tab;
	int		i;
	size_t	nbword;

	i = 0;
	nbword = ft_nb_word(s);
	tab = (char **)malloc(sizeof(char *) * (nbword + 1));
	if (!tab)
		return (NULL);
	while (nbword--)
	{
		while (*s && *s <= 32)
			s++;
		tab[i] = ft_strsub(s, 0, ft_length_word(s));
		if (!tab[i])
			return (NULL);
		s = s + ft_length_word(s);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
