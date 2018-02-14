/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:20:18 by vboivin           #+#    #+#             */
/*   Updated: 2018/02/14 17:24:15 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

void				signal_newline(int inp)
{
	(void)inp;
	write(1, "\n", 1);
}

void				signal_handler(int inp)
{
	(void)inp;
	write(1, "\n", 1);
	write_prompt(g_backup_env);
}

int					filter_cli(char **arr, char fp[], char *cli, t_env *i_env)
{
	int				bin;
	int				wit;

	wit = 0;
	if (!cli || !cli[0])
		return (-1);
	while (*cli && *cli == 32)
		cli++;
	if (!*cli)
		return (-2);
	ft_bzero(fp, MAXPATHLEN * 2 + 1);
	bin = builtin_chk(arr, cli, i_env) ? 1 : 0;
	if (!bin)
		if ((!(ft_strcmp("\\", cli))) || (wit = getpath(arr[0], i_env, fp)) < 0)
		{
			wit == -2 ? 0 :
			pcat("minishell: ", NULL, ": Cannot execute command", 1);
			return (-1);
		}
	if (!fp[0] && !bin)
		derror(arr[0], NULL, NULL, 0);
	else if (fp[0] && !bin)
		edit_specific_var(i_env, "_", fp);
	return (bin);
}

void				exec_cli(char *cli, t_listc *full_detail, t_env *i_env)
{
	char			fullpath[MAXPATHLEN * 2 + 1];
	char			**env;
	int				bin;
	pid_t			father;

	father = 0;
	if ((bin = filter_cli(full_detail->cont, fullpath, cli, i_env)) < 0)
		return ;
	if (!bin && fullpath[0] && !(father = fork()))
	{
		signal(SIGINT, SIG_DFL);
		env = rmk_env(i_env);
		if (full_detail->sep_type == PIPE || full_detail->sep_type == SEPA)
			redirect(full_detail, father);
		if (full_detail->prev && (full_detail->prev->sep_type == AND || full_detail->prev->sep_type == OR))
		{
			if (full_detail->prev->sep_type == OR && i_env->exit_code != 0)
				execve(fullpath, full_detail->cont, env);
			else if (full_detail->prev->sep_type == AND && i_env->exit_code == 0)
				execve(fullpath, full_detail->cont, env);
			else
				exit(i_env->exit_code);
		}
		else
			execve(fullpath, full_detail->cont, env);
		access(fullpath, X_OK) ?
		pcat("minishell: ", fullpath, ": Permission denied.", 1) :
		pcat("minishell: ", fullpath, NEOB, 1);
		exit(-1);
	}
	(!bin && fullpath[0]) ? signal(SIGINT, &signal_newline) : 0;
	waitpid(father, &i_env->status, WUNTRACED);
	i_env->exit_code = WEXITSTATUS(i_env->status);
}

int					main(int ac, char **av, char **env_o)
{
	char			*cli;
	t_env			*env;
	int				read_mode;
	t_histo			*history;

	(void)ac;
	(void)av;
	history = NULL;
	if (!(env = translate_env(env_o, 0)))
		return (-1);
	g_backup_env = env;
	read_mode = terminit(env);
	write_prompt(env);
	signal(SIGINT, &signal_handler);
	while (get_line(read_mode, &cli, &history) > 0)
	{
		read_mode ? tcsetattr(0, TCSADRAIN, &g_termcap_21sh[1]) : 0;
		exec_cli_lst(cli, env);
		signal(SIGINT, &signal_handler);
		write_prompt(env);
		cli ? free(cli) : 0;
	}
	read_mode ? tcsetattr(0, TCSADRAIN, &g_termcap_21sh[1]) : 0;
	//printf("End of transmission\n");
	return (0);
}
