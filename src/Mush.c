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
    cmd[col][0] = '\0';
    
    return(0);
}

/* Executes the command */
int mushExec(char **cmd)
{
    int i;
    pid_t child;
    char *path = cmd[0];
    char **args = malloc(0);
	
    for(i = 0; cmd[i + 1][0] != '\0'; i++) {
	args = realloc(args, i + 1);
	args[i] = cmd[i + 1];
	printf("%d @ %p (%ld):\t%s\n", i, args, sizeof(args), args[i]);
    }
    
    if((child = fork()) == 0) {
	execvp(path, args);
	exit(0);
    } else {
	wait(NULL);
    }

    free(args);
    return(0);
}

/* Deallocates the buffers used to store the
   formatted commands. */
void mushFree(char **cmd)
{
    int i = 0;
    
    do {
	free(cmd[i++]);
    } while(cmd[i][0] != '\0');
    
    free(cmd);
}
