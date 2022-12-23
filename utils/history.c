#include "include/utils.h"

FILE* fp;

int old_cmd_num = 0;  // easy to write new instructions quickly

typedef struct cmdLink {
    char*           cmd;
    struct cmdLink* next;
} cmdLink;

cmdLink* root;

void initHistory() {
    if ((fp = fopen(".history", "a+")) == NULL) {
        show_error(1, "open file \".history\" failed.");
    }

    char *line = NULL, *p = NULL;

    while (!feof(fp)) {
        line = (char*)malloc(sizeof(char) * 1024);
        p    = fgets(line, 1024, fp);

        if (p) {
            add(line);
            old_cmd_num++;
        }
    }
}

void add(char* cmd) {
    cmdLink* n = (cmdLink*)malloc(sizeof(cmdLink));

    n->cmd  = cmd;
    n->next = root;
    root    = n;
}

// reverse linked list
cmdLink* reverse(cmdLink* node) {
    cmdLink *pre = NULL, *cur = node, *next = NULL;

    while (cur) {
        next      = cur->next;
        cur->next = pre;
        pre       = cur;
        cur       = next;
    }

    return pre;
}

void write_to_history() {
    cmdLink* link = reverse(root);

    for (int i = 0; i < old_cmd_num; i++) {
        link = link->next;
    }

    while (link) {
        fprintf(fp, "%s", link->cmd);
        link = link->next;
    }

    fclose(fp);
}

int num = 0;

void input_one_cmd(cmdLink* c) {
    if (c != NULL) {
        input_one_cmd(c->next);
        printf("%d %s", num++, c->cmd);
    }
}

void show_history(int num) {
    input_one_cmd(root);
    num = 0;
}