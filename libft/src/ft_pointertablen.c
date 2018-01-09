/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointertablen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:23:55 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/08 14:27:16 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_pointertablen(char **inp)
{
	int				i;

	i = 0;
	while (inp[i] != NULL)
		i += 1;
	return (i);
}