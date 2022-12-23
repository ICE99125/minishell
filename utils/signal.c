#include "include/utils.h"

void interruptHandler(int signum) {
    write_to_history_and_close();
    exit(EXIT_SUCCESS);
}