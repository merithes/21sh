/*#include "hmini.h"

void    redirect(t_listc *cmd)
{
    if (cmd->redir[1] == 0)
        right_redirect(cmd);
    else if (cmd->redir[1] == 1)
        left_redirect(cmd);
    else if (cmd->redir[1] == 2)
        double_right_redirect(cmd);
    else if (cmd->redir[1] == 3)
        double_left_redirect(cmd);
}

void    right_redirect(t_listc *cmd)
{
    int descfd[2];

    if (cmd->redir[0] && !cmd->file)
    {    
        descfd[0] = redir[2];
        descfd[1] = redir[0];
        //pipe(descfd);
        dup2(descfd[1], STDOUT_FILENO);
    }
}

void    left_redirect(t_listc *cmd)
{
    
}

void    double_right_redirect(t_listc *cmd)
{
    
}

void    double_left_redirect(t_listc *cmd)
{
    
}*/

#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;

    assert(argc == 2);

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    /* Le fils lit dans le tube */
        close(pipefd[1]);  /* Ferme l'extrémité d'écriture inutilisée */

        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } else {                    /* Le père écrit argv[1] dans le tube */
        close(pipefd[0]);       /* Ferme l'extrémité de lecture inutilisée */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);       /* Le lecteur verra EOF */
        wait(NULL);             /* Attente du fils */
        exit(EXIT_SUCCESS);
    }
}
