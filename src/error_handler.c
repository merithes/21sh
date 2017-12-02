/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:27:29 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/31 03:18:39 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				derror(char *cmd, char *path, char *specs, int status)
{
	int				accessd;
	struct stat		statf;

	cmd ?
	pcat("minishell: ", cmd, ":", 0) :
	pcat("minishell: ", NULL, NULL, 0);
	specs ? ft_putstr(specs) : NULL;
	if (status || path)
	{
		path ? lstat(path, &statf) : 0;
		if (!path || (accessd = access(path, F_OK) != 0))
			ft_putstr(NSFOD);
		else if (path && (accessd = access(path, X_OK)) != 0)
			pcat(": ", path, ": Permissions denied", 1);
		else if (path && S_ISLNK(statf.st_mode))
			pcat(": ", path, ": Possible link loop", 1);
		else
			ft_putstr(" Cannot execute command\n");
	}
	else
		write(1, " Cannot execute command\n", 24);
}

void				error_post_exec(char fp[])
{
	struct stat		statf;

	if (lstat(fp, &statf))
	{
		if (access(fp, F_OK))
			pcat("minishell: ", fp, NSFOD, 1);
		else if (access(fp, R_OK))
			pcat("minishell: ", fp, ": Permissions denied", 1);
		else if (access(fp, W_OK))
			pcat("minishell: ", fp, ": Permissions denied", 1);
		else if (access(fp, X_OK))
			pcat("minishell: ", fp, ": Permissions denied", 1);
	}
	else if (S_ISDIR(statf.st_mode))
		pcat("minishell: ", fp, ": Is a directory", 1);
	else if (S_ISLNK(statf.st_mode))
		pcat("minishell: ", fp, ": Link loop", 1);
}
