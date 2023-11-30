# Shell Program in C

## Introduction

This C program is a simple shell implementation that allows users to enter commands. It includes basic features like command execution, handling Ctrl + C, and of course simple string parsing.
[Demo]([Video_URL](https://youtu.be/SgHW8U0RJ_o?si=kuKYSi38QmpzrtiM))

## Code Explanation

### Global Variables

* `char cmd[MAX_CMD_LEN]`:An array of chars to store the user's command

* `char *args[MAX_TOKENS]`: An array of strings to store the tokenized 
command.
* `short int i = 0`: A counter for the number of tokens in the command.

### Functions

* `void readUserCommand(void)`: Displays the shell prompt and reads the user command

* `void tokenizeCommand(void);`: Tokenizes the user command and stores the tokens in the `args`

* `void handleCtrlC(int signum);`: Signal handler for Ctr + c.

* `void runShell(void);`: Main function that runs the shell.

## Usage
```bash
# 1. Create a bin Directory
mkdir bin
# 2. Compile the Program
make
# 3. Run the compiled Program
make run
# 4. Clean the Bin Directory
make clean
```

## Notes
* This version of shell supports only basic commands!
