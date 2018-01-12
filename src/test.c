/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:33:10 by jamerlin          #+#    #+#             */
/*   Updated: 2018/01/12 17:31:49 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/*int main(int argc, char **argv, char **env)
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
}*/

void    ft_pipe(char **argv, int *p, int i)
{
    pid_t father;
    
    pipe(p);
    if ((father = fork()) == -1)
    {
        perror("1fork");
        exit(1);
    }
    if (father == 0)
    {
        execl(argv[0], argv[0], argv[1], NULL);
        exit(EXIT_SUCCESS);
    }
}
int     main(void)
{
    int p[2];
    pid_t father;
    int i;

    i = 0;
    if ((father = fork()) == -1)
    {
        perror("1fork");
        exit(1);
    }
    if (father == 0)
    {
        if (i == 0)
            ft_pipe ((char*[3]){"/bin/ps",NULL,NULL}, p, i);
        if (i == 1)
            ft_pipe((char*[3]){"/bin/cat","-e", NULL}, p , i);
        i++;
    }
    else
        wait(NULL);
    return (0);
}
 
/*int main(void)
{  
    int p[2];
    pid_t pid;
 
    if (pipe(p) == -1) // Lie la sortie standard avec l'entrée standard
    {
        perror("pipe");
        exit(1);
    }
    if ((pid = fork()) == -1) // duplique le processus
    {
        perror("fork");
        exit(1);
    }
    if (pid)
    {
        close(p[0]); // ferme la sortie stantdard
        dup2(p[1],1); // copie l'entre standard vers la sortie standard
        execlp("ls", "ls", "-l", NULL); // execute le processus
        perror("execlp"); 
        exit(1);
    }
    close(p[1]); // ferme l'entree standard
    dup2(p[0], 0); //copie la sortie standard vers l'entrée standard
    if (pipe(p) == -1) 
    {
        perror("pipe"); 
        exit(1);
    }
    if ((pid = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid)
    {
        close(p[0]);
        dup2(p[1],1);
        execlp("grep", "grep", "k_", NULL);
        perror("execlp"); exit(1);
    }
    close(p[1]);
    dup2(p[0], 0);
    execlp("cat", "cat", "-e", NULL);
    perror("execlp");
    exit(1);
}*/