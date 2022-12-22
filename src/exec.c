#include "include/minishell.h"

int is_builtin(char* cmd) {
    if (strcmp(cmd, "cd") == 0) {
        return 1;
    } else if (strcmp(cmd, "export") == 0) {
        return 1;
    } else if (strcmp(cmd, "history") == 0) {
        return 1;
    } else if (strcmp(cmd, "echo") == 0) {
        return 1;
    } else if (strcmp(cmd, "exit") == 0) {
        return 1;
    } else if (strcmp(cmd, "env") == 0) {
        return 1;
    }

    return 0;
}

void exec_builtin(Command* c) {
    if (strcmp(c->cmd, "cd") == 0) {
        cmd_cd(c->args);
    } else if (strcmp(c->cmd, "export") == 0) {
        cmd_export(c->args);
    } else if (strcmp(c->cmd, "history") == 0) {
        cmd_history(c->args);
    } else if (strcmp(c->cmd, "echo") == 0) {
        cmd_echo(c->args);
    } else if (strcmp(c->cmd, "exit") == 0) {
        cmd_exit();
    } else if (strcmp(c->cmd, "env") == 0) {
        cmd_env(c->args);
    }
}

void run_command(Command* c) {
    int status;

    pid_t pid = fork();

    if (pid == 0) {
        // child process
        if (-1 == execvp(c->cmd, c->args)) {
            fprintf(stderr, "command execution error.\n");
        }
    } else if (pid < 0) {
        fprintf(stderr, "create a new process error.\n");
    } else {
        // parent process
        while (1) {
            pid = wait(&status);

            if (pid == -1) {
                break;
            }
        }
    }
}

void exec_command(Command* c) {
    if (is_builtin(c->cmd)) {
        exec_builtin(c);
    } else {
        exec_command(c);
    }
}

// parse user input into an Command array
Command** parse(char* input) {
    char** cmds = strsplit(input, ";\r\n");  // split by ';'

    int buf_s = 2, p = 0;

    Command** res = (Command**)malloc(sizeof(Command*) * buf_s);

    for (int i = 0; NULL != cmds[i]; i++) {
        char** temp = strsplit(cmds[i], " \t");  // split by \t or space

        Command* c = (Command*)malloc(sizeof(Command));
        c->cmd     = temp[0];
        c->args    = temp + 1;
        c->back    = 0;

        if (isBackRun(c->args)) {
            c->back = 1;
        }

        res[p++] = c;

        if (p >= buf_s) {
            // resize
            buf_s *= 2;
            res = (Command**)realloc(res, sizeof(Command*) * buf_s);
        }
    }

    free(cmds);

    res[p] = NULL;  // flag of commands end

    return res;
}

int isBackRun(char** args) {
    int i = 0, b = 0;

    for (int i = 0; NULL != args[i]; i++) {
        if (strcmp(args[i], "&") == 0) {
            b = 1;

            int j = i + 1;
            while (args[j]) {
                free(args[j]);
                j++;
            }

            args[i] = NULL;  // ignore the parameters after &
            break;
        }
    }

    return b;
}