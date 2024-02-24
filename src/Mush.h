/* The maximum length of a input command. */
#define RCMDSIZE 128
#define CMDSIZE 16


int mushLoop();
int mushFormat(char *raw, char **cmd);
void mushFree(char **cmd);
