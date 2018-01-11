/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:08:52 by jamerlin          #+#    #+#             */
/*   Updated: 2018/01/09 18:11:44 by jamerlin         ###   ########.fr       */
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
    cmd->redir[0] = 1;
    cmd->redir[1] = 0;
    cmd->redir[2] = 0;
    cmd->file = ft_strdup(cmd->cont[2]);
    //printf("sep_type = %d\ncontent = %s\nredir[0] = %d\nredir[1] = %d\nredir[2] = %d\nfile = %s\n", cmd->sep_type, cmd->cont[0], cmd->redir[0],cmd->redir[1],cmd->redir[2], cmd->file);
}

void    right_redirect(t_listc *cmd)
{
    int descfd[2];
    
    descfd[0] = (cmd->file) ? open(cmd->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) : cmd->redir[2];
    descfd[1] = cmd->redir[0];
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

void    redirect(t_listc *cmd)
{
    if (!cmd->redir[0])
        return ;
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

