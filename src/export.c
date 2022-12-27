#include "include/minishell.h"

void cmd_export(char** args) {
    // export or export -p
    if (!args[0] || strcmp(args[0], "-p") == 0) {
        show_export();
    } else {
        // export NAME=arcturus DIR=/home
        int i = 0;

        while (args[i]) {
            char** t = strsplit(args[i], "=", false);

            var* v = search_var(t[0]);

            if (v != NULL) {
                v->value  = t[1];
                v->is_env = 1;
            } else {
                add_var(t[0], t[1], 1);
            }

            set_env(t[0], t[1], 1);  // export shell variable to environment variable

            i++;
        }
    }
}