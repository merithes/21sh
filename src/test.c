/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:33:10 by jamerlin          #+#    #+#             */
/*   Updated: 2018/01/08 14:12:23 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv, char **env)
{
    int fd;
    pid_t father;

    fd = open(argv[1], O_RDWR | O_CREAT);
    father = fork();
    if(father == 0)
    {
        dup2(fd, STDOUT_FILENO);
        printf(" haholu");
        close(fd);
        exit(0);
    }
    else 
        wait(NULL);
    printf("ptdr\n");
    return (0);
}