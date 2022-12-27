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
        // echo xxx >> test.txt
        if ((strcmp(args[i], ">>") == 0) || strcmp(args[i], ">") == 0) {
            if (args[i + 1] == NULL) {
                printf("syntax error after \">>\".\n");
            } else {
                int flag = strcmp(args[i], ">>") == 0 ? APPEND : WRITE;
                writeTofile(args[i + 1], msg, flag);
            }

            if (msg != NULL) {
                free(msg);
            }

            return;
        } else {
            // echo "xxx" will become echo xxx
            c = strtrim(args[i], "\"", both);

            char* p = strstr(c, "$");

            if (p != NULL) {
                var* v = search_var(p + 1);

                char* t;

                if (v != NULL) {
                    t = (char*)malloc(sizeof(char) * (p - c + strlen(v->value) + 1));
                    strncpy(t, c, p - c);
                    t[p - c] = '\0';
                    strcat(t, v->value);
                } else {
                    // no variable
                    t = (char*)malloc(sizeof(char) * (p - c + 1));
                    strncpy(t, c, p - c);
                    t[p - c] = '\0';
                }

                new = strjoin(msg, t, " ");

                free(t);
            } else {
                new = strjoin(msg, c, " ");
            }

            free(c);

            if (msg != NULL) {
                free(msg);
            }

            msg = new;
            i++;
        }
    }

    if (msg != NULL) {
        if (n) {
            // echo "xxx"
            printf("%s\n", msg);
        } else {
            // echo -n "xxx" or echo "xxx"
            printf("%s", msg);
        }

        free(msg);
    }
}