/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:08:52 by jamerlin          #+#    #+#             */
/*   Updated: 2018/02/05 14:46:44 by jamerlin         ###   ########.fr       */
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

int     nb_case(char **tabl)
{
    int i;

    i = 0;
    while (tabl[i] != NULL)
        i++;
    return (i);
}

t_listc *add_elem(t_listc *cmd)
{
    t_listc *new;
    t_listc *beg;

    beg = cmd;
    new = (t_listc*)malloc(sizeof(t_listc));
    new->sep_type = 0;
    new->cont = NULL;
    new->nb_arg = 3;
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

t_redir *init_redir(t_redir* lol)
{
    lol = (t_redir*)malloc(sizeof(t_redir));
    lol->redir[0] = OUT; // left = IN | right = OUT| leftleft = | rightright = OUT
    lol->redir[1] = 3; // left = 0; | right = 1 | leftleft = | rightright = 3
    lol->redir[2] = OUT; // left = OUT | right = OUT | leftleft = | rightright = OUT 
    lol->file = "fichier";
    lol->next = NULL;
    return (lol);
}

void    test(t_listc *cmd)
{
    t_listc *beg;
    int i;

    i = 0;
    beg = cmd;
    while (i < 2)
    {
        cmd = add_elem(cmd);
        cmd->redirs = init_redir(cmd->redirs);
        if (i == 0)
        {
            cmd->cont = (char **)malloc(sizeof(char *) * 3);
            cmd->cont[0] = ft_strdup("/bin/ls");
            cmd->cont[1] = ft_strdup("src");
            cmd->cont[2] = NULL;
        }
        else if (i == 1)
        {
            cmd->cont = (char **)malloc(sizeof(char *) * 4);
            cmd->cont[0] = ft_strdup("/usr/bin/grep");
            cmd->cont[1] = ft_strdup("-e");
            cmd->cont[2] = ft_strdup("k_");
            cmd->cont[3] = NULL;
        }
        else if (i == 2)
        {
            cmd->cont = (char **)malloc(sizeof(char *) * 3);
            cmd->cont[0] = ft_strdup("/bin/cat");
            cmd->cont[1] = ft_strdup("-e");
            cmd->cont[2] = NULL;
        }
        cmd->nb_arg = 3;
        cmd = cmd->next;
        i++;
    }
    cmd = beg;
}

void    test_left(t_listc *cmd)
{
    int i;

    i = 0;
    cmd = add_elem(cmd);
    cmd->redirs = init_redir(cmd->redirs);
    if (i == 0)
    {
        cmd->cont = (char **)malloc(sizeof(char *) * 2);
        cmd->cont[0] = ft_strdup("/bin/ls");
        cmd->cont[1] = NULL;
    }
     cmd->nb_arg = 2;
}

void    left_redirect(t_listc *cmd)
{
    int descfd[2];

    descfd[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDONLY) : cmd->redirs->redir[2];
    descfd[1] = cmd->redirs->redir[0];
    printf("%s : %s\n", cmd->cont[0], cmd->redirs->file);
    dup2(descfd[0], descfd[1]);
    close(descfd[0]);
}

void    right_redirect(t_listc *cmd)
{
    int descfd[2];

    descfd[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) : cmd->redirs->redir[2];
    descfd[1] = cmd->redirs->redir[0];
    printf("lol\n");
    dup2(descfd[0], descfd[1]);
    close(descfd[0]);
}

/*void    double_left_redirect(t_listc *cmd)
{
    int descfd[2];

    descfd[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) : cmd->redirs->redir[2];
    descfd[1] = cmd->redirs->redir[0];
    dup2(descfd[0], descfd[1]);
    close(descfd[0]);

}*/

void    double_right_redirect(t_listc *cmd)
{
    int descfd[2];

    descfd[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU ) : cmd->redirs->redir[2];
    descfd[1] = cmd->redirs->redir[0];
    dup2(descfd[0], descfd[1]);
    close(descfd[0]);
}

void    do_pipe(t_listc *cmd, int i, pid_t father, int p[2])
{
    int const READ_END = 0;
    int const WRITE_END = 1;

    if (i == cmd->nb_arg -1 || (cmd->nb_arg == 2 && i == 1))
    {
        close(p[WRITE_END]);
	    dup2(p[READ_END], STDIN_FILENO);
        execve(cmd->cont[0], cmd->cont, NULL);
        perror("execve");
        exit(1);
    }
    else
    {
        if (pipe(p) == -1)
        {
            perror("pipe");
            exit(1);
        }
        if ((father = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }
        if (father == 0)
        {
            close(p[READ_END]);
	        dup2(p[WRITE_END], STDOUT_FILENO);
            execve(cmd->cont[0], cmd->cont, NULL);
            perror("execve");
            exit(1);
        }
        close(p[WRITE_END]);
        dup2(p[READ_END], STDIN_FILENO);
    }
    if (cmd->nb_arg >= 3 && i <= cmd->nb_arg - 2)
    {
        do_pipe(cmd->next, i + 1, father, p);
        ft_putendl_fd("end", 2);
        wait(NULL);
    }
}

void    redirect(t_listc *cmd, pid_t father)
{
    int p[2];

    //(void)father;
    if (cmd->sep_type == 2)
        do_pipe(cmd, 0, father,p);
    /*if (!cmd->redirs || !cmd->redirs->redir[0])
        return ;*/  
    if (cmd->redirs->redir[1] == 0)
        left_redirect(cmd);        
    else if (cmd->redirs->redir[1] == 1)
        right_redirect(cmd);
    /*else if (cmd->redir[1] == 2)
        double_left_redirect(cmd);*/
    else if (cmd->redirs->redir[1] == 3)
        double_right_redirect(cmd);
}

