/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:08:52 by jamerlin          #+#    #+#             */
/*   Updated: 2018/03/13 17:22:36 by jamerlin         ###   ########.fr       */
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

void    left_redirect(t_listc *cmd) //redirection d'un fichier vers une sortie
{
    int descfd[2];
    int ret;
    if (!(ret = open(cmd->redirs->file, O_RDONLY)))
    {
        close(ret);
        exit(1);
    }
    descfd[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDONLY) : cmd->redirs->redir[2];
    descfd[1] = cmd->redirs->redir[0];
    dup2(descfd[0], descfd[1]);
    close(descfd[0]);
}

void right_redirect(t_listc *cmd) //redirection d'une sortie vers un fichier
{
    int descfd[2];
    
    descfd[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) : cmd->redirs->redir[2];
    descfd[1] = cmd->redirs->redir[0];
    dup2(descfd[0], descfd[1]);
    close(descfd[0]);
}

void    double_right_redirect(t_listc *cmd) // redirection d'une sortie vers la fin d'un fichier
{
    int descfd[2];

    descfd[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU ) : cmd->redirs->redir[2];
    descfd[1] = cmd->redirs->redir[0];
    dup2(descfd[0], descfd[1]);
    //close(descfd[0]);
}

void errExit(char *str)
{
    printf("[%s]\n", str);
    exit(1);
}

void     dup_process(int p[2])
{
    if (p[1] != STDOUT_FILENO)
    {
	    if (dup2(p[1], STDOUT_FILENO) == -1)
            errExit("dup 1");
        if (close(p[1]) == -1)
            errExit("close 2");
    }
}

void     dup_last_process(int p[2])
{
    if (p[0]!= STDIN_FILENO)
    {
        if (dup2(p[0], STDIN_FILENO) == -1)
            errExit("dup last");
        if (close(p[0]) == -1)
            errExit("clode last");
    }
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
    while (cpy) 
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
        cpy->nb_arg = nb_cmd ;
        i++;
        //cpy->last = last;
        cpy->prev = cpy;
		cpy = cpy->next;
    }
}

void   redirect(t_listc *cmd) // gestion des redirections
{
    if (cmd->sep_type == PIPE)
        do_pipe(cmd/*, pid_tab,0p*/); // il faut une liste avec les commandes dans des maillons différents
    else
    {
        /*if (!cmd->redirs || !cmd->redirs->redir[0])
            cmd->redirs = init_redir(cmd->redirs);*/
        if (cmd->redirs && cmd->redirs->redir[1] == 0)
            left_redirect(cmd); // une liste de 1 maillon avec le fichier renseigne 
        else if (cmd->redirs && cmd->redirs->redir[1] == 1)
            right_redirect(cmd); // une liste de 1 maillon avec le fichier renseigne
        /*else if (cmd->redir[1] == 2) // doit etre gerer en amont 
            double_left_redirect(cmd);*/
        else if (cmd->redirs && cmd->redirs->redir[1] == 3)
            double_right_redirect(cmd); // une liste de 1 maillon avec le fichier renseigne
    }
}