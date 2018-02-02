/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:08:52 by jamerlin          #+#    #+#             */
/*   Updated: 2018/02/02 16:40:25 by jamerlin         ###   ########.fr       */
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
    new->sep_type = 2;
    new->cont = NULL;
    new->nb_arg = 3;
    new->redirs = NULL;
    new->prev = NULL;
    new->next = NULL;
    if (cmd == NULL)
    {
        return(new);
    }
    while (cmd->next != NULL)
        cmd = cmd->next;
    cmd->next = new;
    cmd->next->next = NULL;
    return (beg);
}

t_redir *init_redir(t_redir* lol)
{
    lol = (t_redir*)malloc(sizeof(t_redir));
    lol->redir[0] = 1;
    lol->redir[1] = 0;
    lol->redir[2] = 0;
    lol->file = NULL;
    lol->next = NULL;
    return (lol);
}

void    test(t_listc *cmd)
{
    t_listc *beg;
    int i;

    i = 0;
    beg = cmd;
    while (i < 3)
    {
        cmd = add_elem(cmd);
        cmd->redirs = init_redir(cmd->redirs);
        if (i == 0)
        {
            //printf("-1\n");
            cmd->cont = (char **)malloc(sizeof(char *) * 2);
            cmd->cont[0] = ft_strdup("/bin/ls");
            cmd->cont[1] = NULL;
        }
        else if (i == 1)
        {
            //printf("-2\n");
            cmd->cont = (char **)malloc(sizeof(char *) * 4);
            cmd->cont[0] = ft_strdup("/usr/bin/grep");
            cmd->cont[1] = ft_strdup("-e");
            cmd->cont[2] = ft_strdup("a");
            cmd->cont[3] = NULL;
        }
        else if (i == 2)
        {
            //printf("-3\n");
            cmd->cont = (char **)malloc(sizeof(char *) * 3);
            cmd->cont[0] = ft_strdup("fds");
            cmd->cont[1] = ft_strdup("-e");
            cmd->cont[2] = NULL;
        }
        cmd->nb_arg = 3;
        cmd = cmd->next;
        i++;
    }
    cmd = beg;
    //int j;
    //while (beg->next != NULL)
    //{
     ///   printf("sep_type = %d\n"/* redir[0] = %d\nredir[1] = %d\nredir[2] = %d\nfile = %s\n" */, 
       //     beg->sep_type/*, cmd->redirs->redir[0],cmd->redirs->redir[1],cmd->redirs->redir[2], cmd->redirs->file)*/);
        //j = 0;
       // while (beg->cont[j])
         //   printf("content = %s ",beg->cont[j++]);
        //printf("\n");
        //beg = beg->next;
    //}
    
}

void    right_redirect(t_listc *cmd)
{
    int descfd[2];
    
    descfd[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) : cmd->redirs->redir[2];
    descfd[1] = cmd->redirs->redir[0];
    dup2(descfd[0], descfd[1]);
    close(descfd[0]);
}

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
        //printf("%s\n", cmd->cont[0]);
        ft_putendl_fd("end cmd", 2);
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
            ft_putendl_fd(cmd->cont[0], 2);
            execve(cmd->cont[0], cmd->cont, NULL);
            perror("execve");
            exit(1);
        }
        ft_putendl_fd("X", 2);
        close(p[WRITE_END]);
        dup2(p[READ_END], STDIN_FILENO);
        wait(NULL);
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

    (void)father;
    if (cmd->sep_type == 2)
        do_pipe(cmd, 0, 0,p);
    if (!cmd->redirs || !cmd->redirs->redir[0])
        return ;
    if (cmd->redirs->redir[1] == 0)
        right_redirect(cmd);
    /*else if (cmd->redir[1] == 1)
        left_redirect(cmd);*/
    else if (cmd->redirs->redir[1] == 2)
        double_right_redirect(cmd);
    /*else if (cmd->redir[1] == 3)
        double_left_redirect(cmd);*/
}

/*void    left_redirect(t_listc *cmd)
{
    
}

void    double_left_redirect(t_listc *cmd)
{
    
}*/

