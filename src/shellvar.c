#include "include/minishell.h"

extern char** environ;

var* node = NULL;

void initShell() {
    int  i = 0;
    var* p = NULL;

    while (environ[i]) {
        char** t = strsplit(environ[i], "=");
        add_var(t[0], t[1], 1);
        i++;
    }
}

void add_var(char* key, char* value, int isEnv) {
    var* p = (var*)malloc(sizeof(var));

    p->isEnv = isEnv;
    p->next  = node;
    p->key   = key;
    p->value = value;
    node     = p;
}

void show_export() {
    var* p = node;

    while (p) {
        if (p->isEnv) {
            printf("declare -x %s=\"%s\"\n", p->key, p->value == NULL ? "" : p->value);
        }

        p = p->next;
    }
}

var* search_var(char* key) {
    var* p = node;

    while (p) {
        if (strcmp(key, p->key) == 0) {
            return p;
        }

        p = p->next;
    }

    return NULL;
}