#include "include/minishell.h"

void run() {
    welcome_to_shell();
    initHistory();
    signal(SIGINT, interruptHandler);

    char* input;       // user input
    int   status = 1;  // whether to exit the shell

    while (status) {
        prompt_msg();

        size_t buffer_size = 0;
        getline(&input, &buffer_size, stdin);
        add(input);

        Command** list = parse(input);

        for (int i = 0; NULL != list[i]; i++) {
            exec_command(list[i]);
        }

        free(list);
    }
}
