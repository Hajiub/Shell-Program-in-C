/* Note: you can't use `|`  `&` */
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



void handleCtrlC(int signum)
{
    (void)signum;
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
            pid_t pid;
            tokenizeCommand();
            /* exit! */
            if (!strcmp(args[0], "exit"))
            {
                break;
            }
            else if(!strcmp(args[0], "cd"))
            {
                printf("Where you going?\n");
                continue;
            }
            pid = fork();
            /* Error */
            if (pid < 0)
            {
                printf("Error: fork.\n");
                exit(EXIT_FAILURE);
            }
            /* child */
            else if (pid == 0)
            {
                if(execvp(args[0], args))
                {
                    printf("%s: command not found\n", args[0]);
                    exit(EXIT_FAILURE);
                }
            }
            /* Parent */
            else
            {
                waitpid(pid, NULL, 0);
            }
        }
    }
    
}
