#include "include/minishell.h"

void cmd_history(char** args) {
    if (args[0] != NULL) {
        if (strcmp(args[0], "-c") == 0) {
            clear_history();
        } else if (strcmp(args[0], "-a") == 0) {
            write_to_history(true);
        } else if (isDigit(args[0])) {
            if (args[0][0] == '-') {
                // history -20
                printf("history: %s : invalid option.\n", args[0]);
            } else {
                // history 10
                show_history(atoi(args[0]));
            }
        } else {
            printf("history: %s : need a numeric argument.\n", args[0]);
        }
    } else {
        // show all history
        show_history(-1);
    }
}