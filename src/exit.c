#include "include/minishell.h"

// kills the shell gracefully
void cmd_exit() {
    write_to_history_and_close();
    exit(EXIT_SUCCESS);
}