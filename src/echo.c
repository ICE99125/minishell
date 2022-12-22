#include "include/minishell.h"

void cmd_echo(char** args) {
    int n = 1 /* newline */, options = 0;

    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "-n") == 0) {
            n = 0;  // don't wrap
            options++;
        } else {
            break;
        }
    }

    int   i   = options;
    char *msg = NULL, *c = NULL, *new = NULL;

    while (args[i] != NULL) {
        // echo "xxx" will become echo xxx
        c   = strtrim(args[i], "\"", both);
        new = strjoin(msg, c, " ");

        free(c);

        if (msg != NULL) {
            free(msg);
        }

        msg = new;
        i++;
    }

    if (strcmp(msg, "") != 0) {
        if (n) {
            // echo "xxx"
            printf("%s\n", msg);
        } else {
            // echo -n "xxx" or echo "xxx"
            printf("%s", msg);
        }
    }

    free(msg);
}