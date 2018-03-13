/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:33:10 by jamerlin          #+#    #+#             */
/*   Updated: 2018/03/01 17:25:12 by jamerlin         ###   ########.fr       */
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
#define SON 0

void    set_fd_pipe(int p[2])
{
    close(p[0]);
    dup2(p[1], STDOUT_FILENO);
}

void    set_fd_standard(int p[2])
{
    close(p[1]);
    dup2(p[0], STDIN_FILENO);
}

int     run_process(int p[2], int i)
{
    set_fd_pipe(p);
    //printf("%d\n", i);
    if (i == 0)
        execve("/bin/cat" , (char*[3]){"/bin/cat","-e",NULL},NULL);
    if (i == 1)
        execve("/usr/bin/grep" , (char*[3]){"/usr/bin/grep","k_",NULL},NULL);
    perror("execve");
    exit(1);
}

void    test(int i, int p[2], pid_t father, int nb_args)
{
    int const	READ_END = 0;
	int const	WRITE_END = 1;
    int status;

    //(WEXITSTATUS(status) != 0) ? printf("exit\n") : printf("ok\n");
    if (i == nb_args -1 || (nb_args == 2 && i == 1))
    {
        set_fd_standard(p);
        //printf("%d\n", i);
        execve("/bin/ls",(char*[2]){"/bin/ls",NULL},NULL);
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
            run_process(p, i);
        }
        set_fd_standard(p);
    }
    if (nb_args >= 2 && i <= nb_args - 2)
    {
        test(i + 1, p, father, nb_args);
        waitpid(father, &status, WUNTRACED);
    }
}

int     main(void)
{
    int p[2];
    pid_t father;

    test(0, p, father, 3);
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