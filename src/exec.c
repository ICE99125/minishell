#include "include/minishell.h"

Command* newCommand(char* input) {
    char** t = strsplit(input, " \t", true);  // split by \t or space

    alias_handler(&t);

    Command* c = (Command*)malloc(sizeof(Command));
    add_recycle(c);

    c->cmd  = t[0];
    c->args = t;
    c->raw  = input;
    c->next = NULL;

    // args_handler(c);
}

char* builtin[] = { "cd", "export", "history", "echo", "env", NULL };

int is_builtin(char* cmd) {
    int i = 0;

    while (builtin[i]) {
        if (strcmp(cmd, builtin[i++]) == 0) {
            return true;
        }
    }

    return false;
}

void exec_builtin(Command* c) {
    if (strcmp(c->cmd, "cd") == 0) {
        cmd_cd(c->args + 1);
    } else if (strcmp(c->cmd, "export") == 0) {
        cmd_export(c->args + 1);
    } else if (strcmp(c->cmd, "history") == 0) {
        cmd_history(c->args + 1);
    } else if (strcmp(c->cmd, "echo") == 0) {
        cmd_echo(c->args + 1);
    } else if (strcmp(c->cmd, "env") == 0) {
        cmd_env(c->args + 1);
    }
}

void exec_command(Command* c) {
    int status;

    pid_t pid = fork();

    if (0 == pid) {
        // child process
        if (is_builtin(c->cmd)) {
            exec_builtin(c);
        } else {
            if (-1 == execvp(c->cmd, c->args)) {
                fprintf(stderr, "command execution error.\n");
            }
        }
    } else if (pid < 0) {
        fprintf(stderr, "create a new process error.\n");
    } else {
        // parent process
        while (true) {
            pid = wait(&status);

            if (-1 == pid) {
                break;
            }
        }
    }
}

Command* reverse_link(Command* n) {
    Command *pre = NULL, *cur = n, *next = NULL;

    while (cur) {
        next      = cur->next;
        cur->next = pre;
        pre       = cur;
        cur       = next;
    }

    return pre;
}

// parse user input into an Command array
Command* parse(char* input) {
    char** cmds = strsplit(input, ";\r\n", true);  // split by ';'
    char **temp = NULL, **t = NULL;

    Command* res = NULL;

    for (int i = 0; NULL != cmds[i]; i++) {
        temp = strsplit(cmds[i], "|", true);

        for (int j = 0; NULL != temp[j]; j++) {
            if (strstr(temp[j], "=") != NULL) {
                // NAME=123
                t = strsplit(temp[j], "=", false);
                add_var(t[0], t[1], 0);
            } else {
                Command* c = newCommand(temp[j]);

                c->next = res;
                res     = c;
            }
        }
    }

    return reverse_link(res);
}

// shallow copy
Command* clone_command(Command* c) {
    Command* cc = (Command*)malloc(sizeof(Command));
    add_recycle(cc);

    cc->args     = c->args;
    cc->back     = c->back;
    cc->cmd      = c->cmd;
    cc->redirect = c->redirect;
    cc->raw      = c->raw;
    cc->next     = NULL;
    cc->path     = c->path;

    return cc;
}

int args_handler(Command* c) {
    char** args = c->args;

    for (int i = 0; NULL != args[i]; i++) {
        if (strcmp(args[i], ">>") == 0 || strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0) {
            if (strcmp(args[i], ">>") == 0) {
                c->redirect = R_DRIGHT;
            } else if (strcmp(args[i], ">") == 0) {
                c->redirect = R_RIGHT;
            } else if (strcmp(args[i], "<") == 0) {
                c->redirect = R_LEFT;
            }

            if (args[i + 1] == NULL || strcmp(args[i + 1], "&") == 0) {
                fprintf(stderr, "syntax error after \"%s\".\n", args[i]);
            }

            int j = i + 2;
            while (args[j]) {
                if (strcmp(args[j], "&") == 0) {
                    c->back = 1;
                    break;
                }

                j++;
            }

            args[i] = NULL;
        }
    }
}