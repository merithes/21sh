/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ferror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:42:21 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/06 17:19:04 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

int					ft_error(char *inp, int nerror)
{
	if (inp)
		ft_putstr_fd(inp, 2);
	tcsetattr(0, TCSADRAIN, &g_termcap_21sh[1]);
	exit(nerror);
}
