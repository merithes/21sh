#include <sys/types.h> // Types prédéfinis "c"
#include <sys/wait.h>  // Attente fin de process
#include <unistd.h>	// Standards Unix
#include <stdio.h>	 // I/O fichiers classiques
#include <fcntl.h>	 // Contrôle fichiers bas niveau
#include <stdlib.h>	// Standard librairies
// Structure qui gère les processus à lancer

#include "hmini.h"

void fermeture(int fils, int nb_tube, t_pipe *tabTube)
{
	int i;

	i = 0;
	while (i < nb_tube)
	{
		if (i != (fils - 1))
			close(tabTube[i].cote[0]);
		if (i != fils)
			close(tabTube[i].cote[1]);
		i++;
	}
}

void ft_cmd_pipe(t_listc *cmd)
{
	char fullpath[MAXPATHLEN * 2 + 1];

	if (filter_cli(cmd->cont, fullpath, cmd->cont[0], g_backup_env) < 0)
		return;
	execve(fullpath, cmd->cont, NULL);
	errExit("execve");
}

void pipe_tmp(t_listc *cmd, int i, t_pipe *tabTube)
{
	//fprintf(stderr, "fils (%d) - pid=%d\n", i, getpid());
	// Fermeture tubes inutilisés par ce processus
	fermeture(i, cmd->nb_arg - 1, tabTube);
	if (i > 0)
	{
		// Redirection entrée venant du tube précédent
		close(STDIN_FILENO);
		dup2(tabTube[i - 1].cote[0], STDIN_FILENO);
	}
	// Pour tous les fils autres que le dernier
	if (i < (cmd->nb_arg - 1))
	{
		// Redirection sortie sur mon tube
		close(STDOUT_FILENO);
		dup2(tabTube[i].cote[1], STDOUT_FILENO);
	}
	ft_cmd_pipe(cmd);
}

void ft_pipe(t_listc *cmd, int *pid_tab, t_pipe *tabTube, int i)
{
	pid_t son;

	son = -1;
	son = fork();
	if (son == -1)
	{
		close(tabTube[i].cote[0]);
		close(tabTube[i].cote[1]);
		perror("fork");
		exit(1);
	}
	else if (son == 0)
		pipe_tmp(cmd, i, tabTube);
	pid_tab[i] = son;
}

int	do_pipe(t_listc *cmd, int *pid_tab, t_pipe *tabTube)
{
	int status;
	int nu_cmd;
	int wt_cpt;
	//t_listc *beg;
	t_listc *cpy;

	status = 0;
	nu_cmd = 0;
	wt_cpt = 0;
	cpy = cmd;
	while(nu_cmd < cmd->nb_arg - 1)
	{
		ft_pipe(cmd, pid_tab, tabTube, nu_cmd);
		cmd = cmd->next;
		nu_cmd++;
	}
	signal(SIGINT, SIG_IGN);
	ft_pipe(cmd, pid_tab, tabTube, nu_cmd);
	fermeture(-1, cmd->nb_arg - 1, tabTube);
	while (wt_cpt < cmd->nb_arg)	
	{
		waitpid(pid_tab[wt_cpt], &cpy->status, 0);
		//if (cpy->status != 0)
			status = cpy->status;
		cpy = cpy->next;
		wt_cpt++;
	}
	return (status);
}

int init_pipe(t_listc *cmd)
{
	int *pid_tab;
	int i;
	t_pipe *tabTube;

	i = 0;
	if (!(tabTube = (t_pipe *)malloc((cmd->nb_arg) * sizeof(t_pipe))))
		exit(-1);
	if (!(pid_tab = (int *)malloc(sizeof(int) * (cmd->nb_arg + 1))))
		exit(-1);
	while (i < (cmd->nb_arg - 1))
	{
		if (pipe(tabTube[i].cote) != 0)
		{
			perror("pipe");
			free(tabTube);
			exit(-2);
		}
		i++;
	}
	return (do_pipe(cmd, pid_tab, tabTube));
}