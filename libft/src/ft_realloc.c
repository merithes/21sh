/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:16:41 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/23 06:07:22 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_realloc(void *inp_o, int qty)
{
	int			i;
	char		*inp;
	char		*outp;

	inp = (char *)inp_o;
	if (!(outp = ft_strnew(qty)))
		return (NULL);
	i = -1;
	while (++i < qty)
		outp[i] = inp[i];
	free(inp);
	return (outp);
}
