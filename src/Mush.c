#include "Mush.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


/* In future, add some arguments (e.g: -r for
   non-interactive mode or something). */
int main(int argc, char *argv[])
{
    mushLoop();
    return(0);
}

/* mushLoop ends when only "exit" is typed. */
int mushLoop()
{
    char *rawCmd = malloc(RCMDSIZE);
    char **cmd;

    do {
	cmd = malloc(RCMDSIZE / CMDSIZE);

	printf("$ ");
	fgets(rawCmd, RCMDSIZE, stdin);
	mushFormat(rawCmd, cmd);

	mushExec(cmd);

	mushFree(cmd);
    } while(strcmp(rawCmd, "exit\n"));

    return(0);
}

/* Creates a 2d list of the command. */
int mushFormat(char *raw, char **cmd)
{
    int i = 0;
    int row = 0;
    int col = 0;

    cmd[col] = malloc(CMDSIZE);

    while(raw[i] != '\n') {
	switch(raw[i]) {
	case ' ':
	    cmd[col][row] = '\0';
	    row = 0;
	    i++;
	    cmd[++col] = malloc(CMDSIZE);

	default:
	    cmd[col][row++] = raw[i++];
	}
    }

    cmd[col][row] = '\0';
    cmd[++col] = malloc(1);
    cmd[col] = NULL;
    
    return(0);
}

/* Executes the command */
int mushExec(char **cmd)
{
    if(fork() == 0) {
	execvp(cmd[0], cmd);
	exit(0);
    } else wait(NULL);
    
    return(0);
}

/* Deallocates the buffers used to store the
   formatted commands. */
void mushFree(char **cmd)
{
    int i = 0;
    
    do {
	free(cmd[i++]);
    } while(cmd[i] != NULL);
    
    free(cmd);
}
