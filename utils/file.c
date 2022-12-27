#include "include/utils.h"

FILE* file = NULL;

void writeTofile(char* dst, char* content, int mode) {
    char* m = mode == WRITE ? "w" : "a";
    char* c = content == NULL ? "" : content;

    if ((file = fopen(dst, m)) == NULL) {
        show_error(1, "open file \"%s\" failed.", dst);
    }

    fprintf(file, "%s\n", c);
    fclose(file);
}