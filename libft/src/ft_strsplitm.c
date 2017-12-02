/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <vboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:57:23 by vboivin           #+#    #+#             */
/*   Updated: 2017/09/13 21:02:08 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_tabsize(char *s)
{
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (s[i])
	{
		i += (s[i] <= 32) ? 1 : 0;
		while (s[i] > 32 && s[i])
		{
			size++;
			i++;
		}
	}
	return (size);
}

static int	ft_len(char *s, int start)
{
	int		len;

	len = 0;
	while (s[start] > 32 && s[start])
	{
		len++;
		start++;
	}
	return (len);
}

static char	*ft_createstr(char *s, char *s2, int start)
{
	int		i;

	i = 0;
	while (s[start] && s[start] > 32)
	{
		s2[i] = s[start];
		i++;
		start++;
	}
	s2[i] = '\0';
	return (s2);
}

static char	**ft_createtab(char **tab, char *s, int start)
{
	int		len;
	int		i;
	int		j;

	i = start;
	j = 0;
	while (s[i])
	{
		len = ft_len(s, start);
		tab[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!(tab[j]))
			return (NULL);
		tab[j] = ft_createstr(s, tab[j], start);
		j++;
		i += ft_len(s, start);
		while (s[i] <= 32 && s[i])
			i++;
		start = i;
	}
	tab[j] = 0;
	return (tab);
}

char		**ft_strsplitw(char const *s)
{
	char	**tab;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	size = ft_tabsize((char *)s);
	if (!(tab = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	ft_memset(tab, 0, sizeof(char *) * size + 1);
	i = 0;
	if (tab)
	{
		while (s[i] <= 32 && s[i])
			i++;
		tab = ft_createtab(tab, (char *)s, i);
		return (tab);
	}
	return (NULL);
}
