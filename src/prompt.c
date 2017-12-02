/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:29:13 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/23 07:40:20 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

static int			get_prompt_env(t_env *root, char *look_for)
{
	t_env			*cursor;
	int				len;

	if (!look_for || !root)
		return (0);
	if (!(cursor = get_env_var(look_for, root)))
	{
		write(1, look_for, len = (int)ft_strlen(look_for));
		return (len);
	}
	else
	{
		write(1, cursor->cont, len = (int)ft_strlen(cursor->cont));
		return (len);
	}
}

static int			prompt_spec(char *inp, t_env *root)
{
	if (!inp || !root)
		return (0);
	if (inp[1] == 'u')
		get_prompt_env(root, "USER");
	else if (inp[1] == 's')
		get_prompt_env(root, "SHLVL");
	else if (inp[1] == 'p')
		get_prompt_env(root, "PWD");
	return (2);
}

static void			print_prompt(char *inp, t_env *root)
{
	while (*inp)
	{
		inp += (*inp == '\\') ? prompt_spec(inp, root) : 0;
		write(1, inp++, 1);
	}
}

void				write_prompt(t_env *env)
{
	t_env			*prompt_var;

	if ((prompt_var = get_env_var("PS1", env)) != NULL)
	{
		if (prompt_var->cont)
			print_prompt(prompt_var->cont, env);
		else
			write(1, "default_prompt>_ ", 17);
	}
	else
		write(1, "default_prompt>_ ", 17);
}
