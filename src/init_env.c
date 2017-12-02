/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 23:20:15 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/27 00:40:00 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

t_env				*create_root_var(void)
{
	t_env			*outp;

	if (!(outp = malloc(sizeof(t_env))))
		return (NULL);
	outp->name = NULL;
	outp->cont = NULL;
	outp->full = NULL;
	outp->next = NULL;
	return (outp);
}

t_env				*creat_var(char *name, char *cont, char *full, int allc)
{
	t_env			*outp;

	if ((!name) && full)
		name = get_cut_env(full, 0);
	if ((!cont) && full)
		cont = get_cut_env(full, 1);
	if (!(outp = malloc(sizeof(t_env))))
		return (NULL);
	outp->name = (allc & MONE) ? name : ft_strdup(name);
	outp->cont = (allc & MTWO) ? cont : ft_strdup(cont);
	outp->next = NULL;
	if (allc & MFOU && !name && !cont)
		outp->full = full;
	else
	{
		if (!(outp->full = malloc(ft_strlen(name) + ft_strlen(cont) + 3)))
			return (NULL);
		ft_bzero(outp->full, ft_strlen(name) + ft_strlen(cont) + 3);
		ft_strcat(outp->full, outp->name);
		ft_strcat(outp->full, "=");
		outp->cont ? ft_strcat(outp->full, outp->cont) : NULL;
	}
	return (outp);
}

t_env				*init_env(void)
{
	t_env			*env;
	t_env			*cursor;
	char			*temp;

	ft_putstr(N_ENV);
	if (!(temp = getcwd(NULL, 0)))
		return (NULL);
	(!(env = create_root_var())) ? exit(-1) : 0;
	(!(env->next = creat_var("PWD", temp, NULL, MTWO))) ?
		exit(-1) : 0;
	cursor = env->next;
	(!(cursor->next = creat_var("PS1", DEF_PROMPT, NULL, 0))) ?
		exit(-1) : (void)(cursor = cursor->next);
	(!(cursor->next = creat_var("OLDPWD", NULL, env->full, 0))) ?
		exit(-1) : (void)(cursor = cursor->next);
	(!(cursor->next = creat_var("SHLVL", "1", 0, 0))) ?
		exit(-1) : (void)(cursor = cursor->next);
	(!(cursor->next = creat_var("PATH", DEF_PATH, 0, 0))) ?
		exit(-1) : (void)(cursor = cursor->next);
	(!(cursor->next = creat_var("PS1", DEF_PROMPT, 0, 0))) ?
		exit(-1) : 0;
	return (env);
}

t_env				*new_var(t_env *root, char *name, char *cont, int allc)
{
	t_env			*outp;

	if (!name && !cont && !allc)
	{
		outp = malloc(sizeof(t_env));
		outp->name = NULL;
		outp->cont = NULL;
		outp->full = NULL;
		outp->next = NULL;
	}
	else
		outp = creat_var(name, cont, NULL, allc);
	if (!root)
		return (outp);
	while (root->next)
		root = root->next;
	root->next = outp;
	return (outp);
}

void				increment_shlvl(t_env *inp)
{
	t_env			*cursor;

	if (!(cursor = get_env_var("SHLVL", inp)))
		return ;
	edit_var_content(cursor, ft_itoa(ft_atoi(cursor->cont) + 1), 1);
}
