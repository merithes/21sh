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

int					ft_error(char *inp, int nerror)
{
	if (inp)
		ft_putstr(inp);
	tcsetattr(0, TCSADRAIN, &termcap_21sh[1]);
	exit(nerror);
}
