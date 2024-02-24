#include "Mush.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* In future, add some arguments (e.g: -r for
   non-interactive mode or something */
int main(int argc, char *argv[])
{
    mushLoop();
    return(0);
}

/* mushLoop ends when only "exit" is typed */
int mushLoop()
{
    char *rawCmd = malloc(RCMDSIZE);
    char **cmd = malloc(RCMDSIZE / CMDSIZE);

    do {
	fgets(rawCmd, RCMDSIZE, stdin);
	mushFormat(rawCmd, cmd);
    } while(strcmp(rawCmd, "exit\n"));

    free(rawCmd);
    return(0);
}

/* Creates a 2d list of the command */
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
	} cmd[col][row] = '\0';
    }

    return(0);
}
