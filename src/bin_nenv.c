/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_nenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:28:29 by vboivin           #+#    #+#             */
/*   Updated: 2017/12/02 15:46:05 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				repath(char **arr, t_env *env, char fp[])
{
	t_env			*cursor;

	if (!arr[1] || ft_strrchr(arr[1], '~'))
	{
		if (!(cursor = get_env_var("HOME", env)))
		{
			ft_putstr("HOME not set.\n");
			return ;
		}
		ft_strcat(fp, cursor->cont);
		if (arr[1] && arr[1][1])
			ft_strcat(fp, arr[1] + 1);
	}
	else if (!ft_strcmp(arr[1], "-"))
	{
		if (!(cursor = get_env_var("OLDPWD", env)))
		{
			ft_putstr("OLDPWD not set.\n");
			return ;
		}
		ft_strncpy(fp, cursor->cont, MPL);
		pcat(fp, NULL, NULL, 1);
	}
	else
		ft_strncpy(fp, arr[1], MAXPATHLEN);
}

void				cd_bin(char **arr, t_env *env)
{
	t_env			*pwd[2];
	t_env			*tmp;
	char			*cwd;
	char			chd[MAXPATHLEN + 1];

	ft_bzero(chd, MPL + 1);
	repath(arr, env, chd);
	if (chdir(chd) < 0)
		derror("cd", chd, NULL, 1);
	else
	{
		cwd = getcwd(NULL, 0);
		tmp = get_env_var("PWD", env);
		pwd[0] = tmp ? tmp : new_var(env, "PWD", cwd, 0);
		tmp = get_env_var("OLDPWD", env);
		pwd[1] = tmp ? tmp : new_var(env, "OLDPWD", cwd, 0);
		edit_var_content(pwd[1], pwd[0]->cont, 1);
		edit_var_content(pwd[0], cwd, 0);
	}
}

void				echo_bin(char **arr, char *cmd, t_env *env)
{
	int				i;

	if (!arr || !cmd || !env)
		return ;
	cmd = skip_cmd(cmd, 5);
	i = 0;
	if (ft_strchr(cmd, '"'))
		while (arr[++i])
			ft_putstr(arr[i]);
	else
		ft_putstr(cmd);
	write(1, "\n", 1);
}

void				exit_bin(char **arr, char *cmd, t_env *env)
{
	int				i;

	i = 0;
	free_list(env);
	while (arr && arr[i])
		free(arr[i++]);
	arr ? free(arr) : 0;
	cmd ? free(cmd) : 0;
	tcsetattr(0, TCSADRAIN, &termcap_21sh[1]);
	exit(0);
}
