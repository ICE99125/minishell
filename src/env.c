#include "include/minishell.h"

void cmd_env(char** args) {
    if (!args[0]) {
        // env
        show_all_env();
    } else if (strcmp(args[0], "-u") == 0) {
        if (!args[1]) {
            printf("env: need an argument.\n");
        } else {
            // env -u HOME
            unset_env(args[1]);
            show_all_env();
        }
    } else {
        // env HOME=/home
        char* p = strstr(args[0], "=");

        if (p) {
            char* key = (char*)malloc(sizeof(char) * (p - args[0] + 1));
            strncpy(key, args[0], p - args[0]);
            key[p - args[0]] = '\0';
            char* value      = strtrim(p + 1, "\"", both);  // remove the double quotation marks
            set_env(key, value, 1);
            free(key);
            free(value);
            show_all_env();
        } else {
            // env sass
            if (access(args[0], F_OK) == -1) {
                printf("env: \"%s\": no such file or directory.\n", args[0]);
            } else if (access(args[0], R_OK) == -1) {
                printf("env: \"%s\": permission denied.\n", args[0]);
            }
        }
    }
}