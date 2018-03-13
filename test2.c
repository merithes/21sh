#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void errExit(char *str)
{
    printf("[%s]\n", str);
    exit(1);
}

int main(int argc, char *argv[])
{
    int pfd[2];          /* Pipe file descriptors */
    int pid;
    char *str = NULL;
    if (pipe(pfd) == -1) /* Create pipe */
        errExit("pipe");
    if ((pid = fork()) == -1)
        errExit("fork");
    else if (pid == 0)
    {                      /* First child: exec 'ls' to write to pipe */
        if (close(pfd[0]) == -1) /* Read end is unused */
            errExit("close 1");
        /* Duplicate stdout on write end of pipe; close duplicated descriptor */
        if (pfd[1] != STDOUT_FILENO)
        { /* Defensive check */
            if (dup2(pfd[1], STDOUT_FILENO) == -1)
                errExit("dup2 1");
            if (close(pfd[1]) == -1)
                errExit("close 2");
        }
        dprintf(2, "exec [cat]\n");
        execlp("cat", "cat","-e", (char *)NULL); /* Writes to pipe */
        errExit("execlp ls");
    }
    if ((pid = fork()) == -1)
        errExit("fork");
    else if (pid == 0)
    {                      /* First child: exec 'ls' to write to pipe */
        if (close(pfd[0]) == -1) /* Read end is unused */
            errExit("close 1");
        /* Duplicate stdout on write end of pipe; close duplicated descriptor */
        if (pfd[1] != STDOUT_FILENO)
        { /* Defensive check */
            if (dup2(pfd[1], STDOUT_FILENO) == -1)
                errExit("dup2 1");
            if (close(pfd[1]) == -1)
                errExit("close 2");
        }
        dprintf(2, "exec [ls]\n");
        execlp("ls", "ls", (char *)NULL); /* Writes to pipe */
        errExit("execlp ls");
    }
    if ((pid = fork()) == -1)
        errExit("fork");
    else if (pid == 0)
    {   
        /* Second child: exec 'wc' to read from pipe */
        if (close(pfd[1]) == -1) /* Write end is unused */
            errExit("close 3");
        /* Duplicate stdin on read end of pipe; close duplicated descriptor */
        if (pfd[0] != STDIN_FILENO)
        { /* Defensive check */
            if (dup2(pfd[0], STDIN_FILENO) == -1)
                errExit("dup2 2");
            if (close(pfd[0]) == -1)
                errExit("close 4");
        }
        dprintf(2, "exec [grep]\n");
        execlp("grep", "grep","M", (char *)NULL); /* Reads from pipe */
        errExit("execlp wc");
    }
    /* Parent closes unused file descriptors for pipe, and waits for children */
    if (close(pfd[0]) == -1)
        errExit("close 5");
    if (close(pfd[1]) == -1)
        errExit("close 6");
    dprintf(2,"lol1 : [%s]\n", str);
    if (wait(NULL) == -1)
        errExit("wait 1");
    dprintf(2,"lol2 : [%s]\n", str);
    if (wait(NULL) == -1)
        errExit("wait 2");
    dprintf(2,"lol3 : [%s]\n", str);
    exit(EXIT_SUCCESS);
}