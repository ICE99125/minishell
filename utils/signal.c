#include "include/utils.h"

void interruptHandler(int signum) {
    write_to_history();
    exit(EXIT_SUCCESS);
}