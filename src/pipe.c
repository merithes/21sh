#include <sys/types.h> // Types prédéfinis "c"
#include <sys/wait.h>  // Attente fin de process
#include <unistd.h>    // Standards Unix
#include <stdio.h>     // I/O fichiers classiques
#include <fcntl.h>     // Contrôle fichiers bas niveau
#include <stdlib.h>    // Standard librairies
// Structure qui gère les processus à lancer

#include "hmini.h"

int			ft_backup_stdin(int nb)
{
	static int stdout = 0;

	if (nb == 1)
		stdout = dup(0);
	return (stdout);
}

int			ft_backup_stdout(int nb)
{
	static int stdout = 0;

	if (nb == 1)
		stdout = dup(1);
	return (stdout);
}

int			ft_backup_stderr(int nb)
{
	static int stdout = 0;

	if (nb == 1)
		stdout = dup(2);
	return (stdout);
}

void    ft_cmd_pipe(t_listc *cmd)
{
    char    fullpath[MAXPATHLEN * 2 + 1];

    if (filter_cli(cmd->cont, fullpath, cmd->cont[0], g_backup_env) < 0)
            return ;
    execve(fullpath, cmd->cont, NULL);
    errExit("execve");
}

void	pipe_tmp(t_listc *cmd, int pd[2])
{
	if (cmd->sep_type == PIPE)
		dup2(pd[1], STDOUT_FILENO);
	close(pd[0]);
	ft_cmd_pipe(cmd);
	exit(1);
}

void    ft_pipe(t_listc *cmd, int *pid_tab)
{
    pid_t   son;
    int     pd[2];
    static  int i = 0;

    son = -1;
    pipe(pd);
    son = fork();
    if (son == -1)
	{
		close(pd[0]);
		close(pd[1]);
		perror("fork");
		exit(1);
	}
	else if (son == 0)
		pipe_tmp(cmd, pd);
	pid_tab[i] = son;
    dprintf(2,"pid_tab[%d] = [%d]\n",i, pid_tab[i]);
    i++;
	if (cmd->sep_type == PIPE)
	{
		dup2(pd[0], STDIN_FILENO);
		close(pd[1]);
	}
}

void do_pipe(t_listc *cmd)
{
    int *pid_tab;
	int i;
    int status;

    i = -1;
    pid_tab = (int *)malloc(sizeof(cmd->nb_arg));
    while (cmd->sep_type == PIPE)
    {
        ft_pipe(cmd, pid_tab);
        cmd = cmd->next;
    }
    signal(SIGINT, SIG_IGN);
    ft_pipe(cmd, pid_tab);
    while (++i < cmd->nb_arg )
    {
        dprintf(2,"fin pid_tab[%d] = [%d]\n",i, pid_tab[i]);
		waitpid(pid_tab[i], &status, 0);
    }
    //errExit (ft_itoa(pid_tab[i]));
}