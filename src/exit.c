#include "include/minishell.h"

// kills the shell gracefully
void cmd_exit() {
    write_to_history();
    exit(EXIT_SUCCESS);
}