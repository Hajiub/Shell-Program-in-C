#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 256
#define MAX_TOKENS 16

char cmd[MAX_CMD_LEN];
char *args[MAX_TOKENS];
short int i = 0;

void readUserCommand(void);
void tokenizeCommand(void);
void freeTokens(void);
void handleCtrlC(int signum);
void runShell(void);

int main()
{
    runShell();
    return 0;
}

void readUserCommand(void)
{
    printf("$ ");
    fgets(cmd, MAX_CMD_LEN, stdin);
    cmd[strcspn(cmd, "\n")] = '\0';
}

void tokenizeCommand(void)
{
    i = 0;
    // args = (char **)malloc(MAX_TOKENS * sizeof(char *));
    // if (args == NULL)
    // {
    //     perror("Error: Couldn't allocate memory for args.\n");
    //     exit(EXIT_FAILURE);
    // }

    char *token;
    char *delim = " ";
    token = strtok(cmd, delim);
    while (token)
    {
        args[i++] = token;
        token = strtok(NULL, delim);
    }

    // Ensure the last element of args is NULL
    args[i] = NULL;
}

void freeTokens(void)
{
    for (int j = 0; j < i; j++)
    {
        free(args[j]);
        args[j] = NULL;
    }
    
    //args = NULL;
}

void handleCtrlC(int signum)
{
    (void)signum;
    //freeTokens();
    exit(EXIT_SUCCESS);
}

void runShell(void)
{   
    // Set up signal handler for Ctrl+C
    if (signal(SIGINT, handleCtrlC) == SIG_ERR)
    {
        perror("Error: Couldn't set up signal handler for Ctrl+C.\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        readUserCommand();
        /* Handle Ctrl + D */
        if (feof(stdin))
        {
            break;
        }
        /* Ignore null Commands */
        else if (strcmp(cmd, "") == 0)
        {
            continue;
        }
        /* Handle commands here! */
        else
        {
            tokenizeCommand();
        }
    }
    
}
