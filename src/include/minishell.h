#ifndef __MINISHELL_H__
#define __MINISHELL_H__

#include "../../utils/include/utils.h"

typedef struct {
    char*  cmd;
    char** args;
    int    back;  // &
} Command;

// minishell.c

void run();

// cd.c

void cmd_cd(char** args);

// exit.c

void cmd_exit();

// env.c

void cmd_env(char** args);

// echo.c

void cmd_echo(char** args);

// exec.c

// built-in command
int is_builtin(char* cmd);

void exec_builtin(Command* c);

Command** parse(char* input);

// execute a command
void exec_command(Command* c);

// whether the command runs in the background
int isBackRun(char** args);

void run_command(Command* c);

// history.c

void cmd_history(char** args);

// export.c

void cmd_export(char** args);

#endif