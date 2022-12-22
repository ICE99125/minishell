#include "include/utils.h"

extern char** environ;

char* get_env(const char* key) {
    char* val = getenv(key);

    if (NULL == val) {
        fprintf(stderr, "cannot find the environment variable \"%s\".\n", key);
    }

    return val;
}

void set_env(const char* key, const char* value, int overwrite) {
    int res = setenv(key, value, overwrite);

    if (-1 == res) {
        fprintf(stderr, "Set enviroment variable \"%s\" failed.\n", key);
    }
}

void put_env(const char* key, const char* value) {
    char* val = getenv(key);

    if (NULL == val) {
        set_env(key, value, 0);
    } else {
        int   len = strlen(val) + strlen(value) + 2;
        char* e   = (char*)malloc(sizeof(char) * len);

        strcpy(e, val);
        strcat(e, ":");
        strcat(e, value);

        set_env(key, e, 1);

        free(e);
    }
}

void unset_env(const char* key) {
    int res = unsetenv(key);

    if (res == -1) {
        fprintf(stderr, "Unset enviroment variable \"%s\" failed.\n", key);
    }
}

void show_all_env() {
    int i = 0;

    while (environ[i]) {
        printf("%s\n", environ[i++]);
    }
}
