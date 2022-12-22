#include "include/utils.h"

int startswith(const char* src, const char* dest) {
    int i = 0;

    while (1) {
        if (*(src + i) || *(src + i) == '\0') {
            if (*(dest + i) == '\0') {
                return 1;
            } else if (*(src + i) == *(dest + i)) {
                i++;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}

int endswith(const char* src, const char* dest) {
    int len1 = strlen(src), len2 = strlen(dest), i = 1;

    if (len1 < len2) return 0;

    while (1) {
        if (i <= len2) {
            if (src[len1 - i] == dest[len2 - i]) {
                i++;
            } else {
                return 0;
            }
        } else {
            return 1;
        }
    }
}

char* strrepl(const char* str, const char* search, const char* replace_with, int all) {
    int len1 = strlen(search), len2 = strlen(replace_with), len3 = strlen(str);

    int len;
    if (len1 >= len2) {
        len = len3 + 1;
    } else {
        // replace_with is longer than search
        // we assume all are search
        // so the number of replacement will not exceed "len3 / len1 + 1"
        len = len3 + 1 + (len3 / len1 + 1) * (len2 - len1);
    }

    char* buf = (char*)malloc(sizeof(char) * len);
    buf[0]    = '\0';

    char* pos = NULL;
    char* p   = (char*)str;

    while ((pos = strstr(p, search)) != NULL) {
        size_t n = (size_t)(pos - p);

        strncat(buf, p, n);
        strcat(buf, replace_with);

        p = pos + len1;

        if (!all) {
            break;
        }
    }

    strcat(buf, p);

    return buf;
}

char** strsplit(const char* source, const char* separator) {
    int buf_s = 2, p = 0;

    // strtok cannot use const char*, so we make a copy.
    char* s = (char*)malloc(sizeof(char) * (strlen(source) + 1));
    strcpy(s, source);

    char** res = (char**)malloc(sizeof(char*) * buf_s);

    char* token = strtok(s, separator);

    while (token != NULL) {
        res[p++] = token;

        if (p >= buf_s) {
            buf_s *= 2;
            res = (char**)realloc(res, buf_s * sizeof(char*));
        }

        token = strtok(NULL, separator);
    }

    res[p] = token;  // end with NULL marker

    return res;
}

char* strtrim(const char* str, const char* flag, Direct direct) {
    int len = strlen(str);
    int i   = 0;

    char* res = (char*)malloc(sizeof(char) * (len + 1));

    if (direct == left) {
        int s = startswith(str, flag);

        if (s) {
            strcpy(res, str + strlen(flag));
        } else {
            strcpy(res, str);
        }
    } else if (direct == right) {
        int s = endswith(str, flag);

        if (s) {
            strncpy(res, str, strlen(str) - strlen(flag));
        } else {
            strcpy(res, str);
        }
    } else if (direct == both) {
        int s1 = startswith(str, flag);
        int s2 = endswith(str, flag);
        int l  = strlen(flag);

        if (s1 && s2) {
            strncpy(res, str + l, len - 2 * l);
        } else if (s1) {
            strcpy(res, str + l);
        } else if (s2) {
            strncpy(res, str, strlen(str) - l);
        } else {
            strcpy(res, str);
        }
    }

    return res;
}

char* strjoin(const char* src, const char* sub, const char* join_with) {
    char* res = NULL;

    if (src == NULL && sub == NULL) {
        res = (char*)malloc(sizeof(char) * 8);
        strcpy(res, "(null)");
    } else if (src == NULL) {
        res = (char*)malloc(sizeof(char) * (strlen(sub) + 1));
        strcpy(res, sub);
    } else if (sub == NULL) {
        res = (char*)malloc(sizeof(char) * (strlen(src) + 1));
        strcpy(res, src);
    } else {
        int len1 = strlen(src), len2 = strlen(sub), len3 = strlen(join_with);
        res = (char*)malloc(sizeof(char) * (len1 + len2 + len3 + 1));

        strcpy(res, src);
        strcat(res, join_with);
        strcat(res, sub);
    }

    return res;
}