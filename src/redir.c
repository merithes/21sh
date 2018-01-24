/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:08:52 by jamerlin          #+#    #+#             */
/*   Updated: 2018/01/24 19:08:20 by jamerlin         ###   ########.fr       */
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

void    test(t_listc *cmd)
{
    cmd->sep_type = 1;
    cmd->redirs->redir[0] = 1;
    cmd->redirs->redir[1] = 0;
    cmd->redirs->redir[2] = 0;
    cmd->file = ft_strdup(cmd->cont[2]);
    printf("sep_type = %d\ncontent = %s\nredir[0] = %d\nredir[1] = %d\nredir[2] = %d\nfile = %s\n", cmd->sep_type, cmd->cont[0], cmd->redir[0],cmd->redir[1],cmd->redir[2], cmd->file);
}

void    right_redirect(t_listc *cmd)
{
    int descfd[2];
    
    descfd[0] = (cmd->file) ? open(cmd->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) : cmd->redir[2];
    descfd[1] = cmd->redirs->redir[0];
    dup2(descfd[0], descfd[1]);
    close(descfd[0]);
}

void    double_right_redirect(t_listc *cmd)
{
    int descfd[2];

    descfd[0] = (cmd->file) ? open(cmd->file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU ) : cmd->redir[2];
    descfd[1] = cmd->redir[0];
    dup2(descfd[0], descfd[1]);
    close(descfd[0]);
}

void    pipe(t_listc *cmd, int i, pid_t father, int p[2])
{
    int const READ_END = 0;
    int const WRITE_END = 1;

    if (i == cmd->nb_arg -1)
    {
        close(descfd[WRITE_END]);
	    dup2(descfd[READ_END], STDIN_FILENO);
        execve(cmd->cont[nb_arg - 1],   )
        //execve("/bin/cat",(char*[3]){"/bin/cat","-e",NULL},NULL);
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
            if (i == 0)
                execve()
                //execve("/bin/ls" , (char*[2]){"/bin/ls",NULL},NULL);
            if (i == 1)
                //execve("/usr/bin/grep" , (char*[3]){"/usr/bin/grep","k_",NULL},NULL);
            perror("execve");
            exit(1);
        }
        close(p[WRITE_END]);
        dup2(p[READ_END], STDIN_FILENO);
    }
    if (nb_args >= 3 && i <= nb_args - 2)
    {
        pipe(cmd, i + 1, p, father);
        wait(NULL);
    }
}

void    redirect(t_listc *cmd)
{
    int p[2];

    if (!cmd->redir[0])
        return ;1
    if (cmd->redir[1] == 0)
        right_redirect(cmd);
    /*else if (cmd->redir[1] == 1)
        left_redirect(cmd);*/
    else if (cmd->redir[1] == 2)
        double_right_redirect(cmd);
    /*else if (cmd->redir[1] == 3)
        double_left_redirect(cmd);*/
}

/*void    left_redirect(t_listc *cmd)
{
    
}

void    double_left_redirect(t_listc *cmd)
{
    
}

void    pipe(t_listc *cmd)
{
    ls | cat (ls = processus fils, cat processus pere), fork tant qu'il y a des pipes; 
}

*/

