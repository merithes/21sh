/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:57:07 by vboivin           #+#    #+#             */
/*   Updated: 2017/12/02 23:16:37 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

int					terror(int inp)
{
	if (inp == -2)
		write(1, "TERM variable not set. ", 23);
	else if (inp == -1)
		write(1, "Terminfo dtabase could not be found. ", 37);
	else if (inp == 0)
		write(1, "TERM variable does not correspond to any Terminfo entry. ",
				57);
	else if (inp == -3)
		write(1, "Something is wrong with the term fildes. ", 41);
	else if (inp == -4)
		write(1, "Some termcap isn't here. ", 25);
	else if (inp == -5)
		write(1, "Couldn't set the termcap attributes correctly. ", 47);
	write(1, "Running canonical mode.\n", 24);
	return (0);
}

int					tc_check(void)
{
	if (!tgetstr("sf", NULL))
		return (-1);
	else if (!tgetstr("ce", NULL))
		return (-1);
	else if (!tgetstr("le", NULL))
		return (-1);
	else if (!tgetstr("up", NULL))
		return (-1);
	return (0);
}

int					terminit(t_env *env)
{
	t_env			*cursor;
	int				err;

	err = -2;
	if (!(cursor = get_env_var("TERM", env)))
		return (terror(-2));
	if (!(cursor->cont) || (err = tgetent(NULL, cursor->cont)) != 1)
		return (terror(err));
	if (tcgetattr(0, &termcap_21sh[0]) == -1 ||
		tcgetattr(0, &termcap_21sh[1]) == -1)
		return (terror(-3));
	termcap_21sh[0].c_lflag &=
		~((unsigned long)(ECHO | ECHOE | ECHOK | ECHONL | ICANON));
	termcap_21sh[0].c_cc[VMIN] = 1;
	termcap_21sh[0].c_cc[VTIME] = 0;
	if (tc_check() < 0)
		return (terror(-4));
	if (tcsetattr(0, TCSADRAIN, &termcap_21sh[0]) == -1)
		return (terror(-5));
	return (1);
}
