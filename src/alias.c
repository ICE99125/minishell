#include "include/minishell.h"

char* args_ll[] = { "-alF", "--color=auto" };

Command ll = {
    .cmd  = "ls",
    .args = args_ll,
    .back = 0,
};

char* args_l[] = { "-CF", "--color=auto" };

Command l = {
    .cmd  = "ls",
    .args = args_l,
    .back = 0,
};

char* args_la[] = { "-A", "--color=auto" };

Command la = {
    .cmd  = "ls",
    .args = args_la,
    .back = 0,
};

char* args_ls[] = { "--color=auto" };

Command ls = {
    .cmd  = "ls",
    .args = args_ls,
    .back = 0,
};

char* args_mv[] = { "-i" };

Command mv = {
    .cmd  = "mv",
    .args = args_mv,
    .back = 0,
};

char* args_rm[] = { "-i" };

Command rm = {
    .cmd  = "rm",
    .args = args_rm,
    .back = 0,
};

char* args_grep[] = { "--color=auto" };

Command grep = {
    .cmd  = "grep",
    .args = args_grep,
    .back = 0,
};

char* args_mkdir[] = { "-pv" };

Command mkdir = {
    .cmd  = "mkdir",
    .args = args_mkdir,
    .back = 0,
};

// array length exclude NULL
int array_len(char** c) {
    int i = 0;
    while (c[i++])
        ;

    return i;
}

int has_alias(char* cmd) {
    if (strcmp(cmd, "ll") == 0) {
        return 1;
    } else if (strcmp(cmd, "l") == 0) {
        return 1;
    } else if (strcmp(cmd, "la") == 0) {
        return 1;
    } else if (strcmp(cmd, "ls") == 0) {
        return 1;
    } else if (strcmp(cmd, "rm") == 0) {
        return 1;
    } else if (strcmp(cmd, "mv") == 0) {
        return 1;
    } else if (strcmp(cmd, "grep") == 0) {
        return 1;
    } else if (strcmp(cmd, "mkdir") == 0) {
        return 1;
    } else {
        return 0;
    }
}

void alias(char*** c) {
    if (has_alias((*c)[0])) {
        int len = array_len(*c) + 3;

        char** t = (char**)malloc(sizeof(char*) * len);

        if (strcmp((*c)[0], "ll") == 0) {
            t[0] = ll.cmd;
            t[1] = ll.args[0];
            t[2] = ll.args[1];

            int i = 0;
            while ((*c)[i + 1]) {
                t[i + 3] = (*c)[i + 1];
                i++;
            }

            t[i + 3] = NULL;
        } else if (strcmp((*c)[0], "ls") == 0) {
            t[0] = ls.cmd;
            t[1] = ls.args[0];

            int i = 0;
            while ((*c)[i + 1]) {
                t[i + 2] = (*c)[i + 1];
                i++;
            }

            t[i + 2] = NULL;
        } else if (strcmp((*c)[0], "la") == 0) {
            t[0] = la.cmd;
            t[1] = la.args[0];
            t[2] = la.args[1];

            int i = 0;
            while ((*c)[i + 1]) {
                t[i + 3] = (*c)[i + 1];
                i++;
            }

            t[i + 3] = NULL;
        } else if (strcmp((*c)[0], "l") == 0) {
            t[0] = l.cmd;
            t[1] = l.args[0];
            t[2] = l.args[1];

            int i = 0;
            while ((*c)[i + 1]) {
                t[i + 3] = (*c)[i + 1];
                i++;
            }

            t[i + 3] = NULL;
        } else if (strcmp((*c)[0], "mv") == 0) {
            t[0] = mv.cmd;
            t[1] = mv.args[0];

            int i = 0;
            while ((*c)[i + 1]) {
                t[i + 2] = (*c)[i + 1];
                i++;
            }

            t[i + 2] = NULL;
        } else if (strcmp((*c)[0], "rm") == 0) {
            t[0] = rm.cmd;
            t[1] = rm.args[0];

            int i = 0;
            while ((*c)[i + 1]) {
                t[i + 2] = (*c)[i + 1];
                i++;
            }

            t[i + 2] = NULL;
        } else if (strcmp((*c)[0], "grep") == 0) {
            t[0] = grep.cmd;
            t[1] = grep.args[0];

            int i = 0;
            while ((*c)[i + 1]) {
                t[i + 2] = (*c)[i + 1];
                i++;
            }

            t[i + 2] = NULL;
        } else if (strcmp((*c)[0], "mkdir") == 0) {
            t[0] = mkdir.cmd;
            t[1] = mkdir.args[0];

            int i = 0;
            while ((*c)[i + 1]) {
                t[i + 2] = (*c)[i + 1];
                i++;
            }

            t[i + 2] = NULL;
        }

        free(*c);
        (*c) = t;
    }
}