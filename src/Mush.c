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


int mushLoop()
{
    char *rawCmd = malloc(RCMDSIZE);

    do {
	fgets(rawCmd, RCMDSIZE, stdin);
    } while(strcmp(rawCmd, "exit\n"));

    free(rawCmd);
    return(0);
}
