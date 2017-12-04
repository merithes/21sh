/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:28:37 by vboivin           #+#    #+#             */
/*   Updated: 2017/12/02 15:21:22 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

char				*skip_cmd(char *inp, int nb)
{
	inp += nb;
	while (*inp && *inp < 32)
		inp++;
	return (inp);
}

static void			chk_exist(char *cmd, char **path, char *fullpath)
{
	struct stat		statf;
	int				i;

	i = 0;
	if (!cmd || !fullpath || !path || !path[0] || !ft_strcmp("\\", cmd)
			|| ft_strlen(cmd) > MAXPATHLEN)
	{
		ft_bzero(fullpath, MAXPATHLEN + 1);
		return ;
	}
	ft_bzero(fullpath, MAXPATHLEN + 1);
	ft_strcat(fullpath, path[i++]);
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, cmd);
	while (lstat(fullpath, &statf) && path[i])
	{
		ft_bzero(fullpath, MAXPATHLEN + 1);
		ft_strcat(fullpath, path[i++]);
		ft_strcat(fullpath, "/");
		ft_strcat(fullpath, cmd);
	}
	if (!(path[i]) && lstat(fullpath, &statf))
		ft_bzero(fullpath, MAXPATHLEN + 1);
}

int					getpath(char *cmd, t_env *env, char *fullpath)
{
	t_env			*cursor;
	char			**content;
	int				i;
	struct stat		statf;

	ft_bzero(fullpath, MAXPATHLEN + 1);
	if ((i = -1) && !lstat(cmd, &statf) && ft_strrchr(cmd, '/'))
	{
		!S_ISDIR(statf.st_mode) ? ft_strcpy(fullpath, cmd) :
			pcat("minishell: ", cmd, ": is a directory.", 1);
		return (S_ISDIR(statf.st_mode) ? -2 : 0);
	}
	if (!(cursor = get_env_var("PATH", env)))
	{
		if (lstat(cmd, &statf))
			return (-1);
		ft_strcpy(fullpath, cmd);
		return (0);
	}
	if (!(content = ft_strsplit(cursor->cont, ':')))
		return (-1);
	chk_exist(cmd, content, fullpath);
	while (content[++i])
		free(content[i]);
	return ((int)(long int)return_free(content));
}

int					builtin_chk(char **arr, char *cmd, t_env *env)
{
	int				wit;

	wit = 6;
	if (!arr[0])
		return (0);
	(!ft_strncmp("exit", arr[0], 5)) ? exit_bin(arr, cmd, env) : wit--;
	(!ft_strncmp("cd", arr[0], 3)) ? cd_bin(arr, env) : --wit;
	(!ft_strncmp("env", arr[0], 4)) ? env_bin(arr, env) : --wit;
	(!ft_strncmp("setenv", arr[0], 7)) ? setenv_bin(arr, cmd, env) : --wit;
	(!ft_strncmp("unsetenv", arr[0], 9)) ? uenv_bin(arr, env) : --wit;
	(!ft_strncmp("echo", arr[0], 5)) ? echo_bin(arr, cmd, env) : --wit;
	return (wit);
}
