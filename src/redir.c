/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:08:52 by jamerlin          #+#    #+#             */
/*   Updated: 2018/03/16 20:37:53 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

t_listc *add_elem2(t_listc *cmd) // ajoute un maillon
{
    t_listc *new;
    t_listc *beg;

    beg = cmd;
    new = (t_listc*)malloc(sizeof(t_listc));
    new->sep_type = SEPA;
    new->cont = NULL;
    new->nb_arg = 2;
    new->redirs = NULL;
    new->prev = NULL;
    new->next = NULL;
    if (cmd == NULL)
        return(new);
    while (cmd->next != NULL)
        cmd = cmd->next;
    cmd->next = new;
    cmd->next->next = NULL;
    return (beg);
}

t_redir *init_redir(t_redir* lol) //init la liste redir
{
    lol = (t_redir*)malloc(sizeof(t_redir)); // init la liste redir
    lol->redir[0] = OUT; // left = IN | right = OUT| leftleft = | rightright = OUT
    lol->redir[1] = 2; // left = 0; | right = 1 | leftleft = | rightright = 3
    lol->redir[2] = OUT; // left = OUT | right = OUT | leftleft = | rightright = OUT 
    lol->file = "fichier";
    lol->next = NULL;
    return (lol);
}

t_redir *init_redir2(t_redir* lol) // init la liste redir
{
    lol = (t_redir*)malloc(sizeof(t_redir));
    lol->redir[0] = OUT; // left = IN | right = OUT| leftleft = | rightright = OUT
    lol->redir[1] = 0; // left = 0; | right = 1 | leftleft = | rightright = 3
    lol->redir[2] = OUT; // left = OUT | right = OUT | leftleft = | rightright = OUT 
    lol->file = "fichier";
    lol->next = NULL;
    return (lol);
}

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

void    left_redirect(t_listc *cmd, t_pipe *tabTube, int i) //redirection d'un fichier vers une sortie
{
    //int descfd[2];
    int ret;
    if (!(ret = open(cmd->redirs->file, O_RDONLY)))
    {
        close(ret);
        exit(1);
    }
    tabTube[i].cote[0] = (cmd->redirs->file) ? ret : cmd->redirs->redir[2];
    tabTube[i].cote[1] = cmd->redirs->redir[0];
    //dup2(descfd[0], descfd[1]);
    //if (cmd->sep_type != PIPE)
        //close(descfd[0]);
}

void right_redirect(t_listc *cmd, t_pipe *tabTube, int i) //redirection d'une sortie vers un fichier
{
    //int descfd[2];
    
    tabTube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) 
    : cmd->redirs->redir[2];
    tabTube[i].cote[1] = cmd->redirs->redir[0];
    //dup2(descfd[0], descfd[1]);
    //close(descfd[0]);
}

void    double_right_redirect(t_listc *cmd, t_pipe *tabTube, int i)// redirection d'une sortie vers la fin d'un fichier
{
    //int descfd[2];

    tabTube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU ) : cmd->redirs->redir[2];
    tabTube[i].cote[1] = cmd->redirs->redir[0];
    //dup2(descfd[0], descfd[1]);
    //close(descfd[0]);
}

void errExit(char *str)
{
    printf("[%s]\n", str);
    exit(1);
}

void    prepare_pipe(t_listc *cmd)
{
    t_listc *cpy;
    t_listc *last;
    int nb_cmd;
    int i;

    cpy = cmd;
    nb_cmd = 0;
    i = 0;
    while (cpy->sep_type == PIPE) 
    {
        last = cpy;
        if (cpy->sep_type == PIPE)
            nb_cmd++;
        cpy = cpy->next;
    }
    cpy = cmd;
    nb_cmd++;
    while (cpy && i < nb_cmd)
    {
        cpy->nb_arg = nb_cmd;
        i++;
        cpy->prev = cpy;
		cpy = cpy->next;
    }
}

void   redirect(t_listc *cmd, t_pipe *tabTube , int i) // gestion des redirections
{
    //static int i = 0;
    int j = 0;

    while (cmd->redirs != NULL)
    {
        if (cmd->redirs && cmd->redirs->redir[1] == 0)
            left_redirect(cmd, tabTube, i); // une liste de 1 maillon avec le fichier renseigne 
        else if (cmd->redirs && cmd->redirs->redir[1] == 1)
            right_redirect(cmd, tabTube, i); // une liste de 1 maillon avec le fichier renseigne
    /*else if (cmd->redir[1] == 2) // doit etre gerer en amont 
        double_left_redirect(cmd);*/
        else if (cmd->redirs && cmd->redirs->redir[1] == 3)
               double_right_redirect(cmd, tabTube, i); // une liste de 1 maillon avec le fichier renseigne
        dprintf(2,"tabTube.cote[0] == [%d] ; tabTube.cote[1] == [%d] ; i == [%d]\n", tabTube[i].cote[0], tabTube[i].cote[1], i/*j**/);
        cmd->redirs = cmd->redirs->next;
        
        dup2(tabTube[i].cote[0], tabTube[i].cote[1]);
        if (cmd->sep_type != PIPE)
        {
            if (cmd->next == NULL)
                close(tabTube[i].cote[1]);
            if (i == 0)
                close(tabTube[i].cote[0]);
        }
        j++;
    }
    i++;
    dprintf(2,"i = [%d]\n",i);
}