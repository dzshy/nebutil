#include "str.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>

char** str_split(char *str, char delim) {
    char **ret;

    if (str == NULL) return NULL;
    if (*str == '\n') {
        ret = malloc(sizeof(char*));
        *ret = NULL;
        return ret;
    }
    int count = 0;
    char *begin = str;
    for (char *p = str; *p != '\0'; p++) {
        if (*p != delim && !(delim == '\0' && isspace(*p))) {
            continue;
        }
        int size = p - begin;
        if (size > 0) count++;
    }
    count++;
    ret = malloc((count + 1) * sizeof(char*));
    memset(ret, 0, (count + 1) * sizeof(char*));

    begin = str;
    int i = 0;
    bool finished = false;
    for (char *p = str; !finished; p++) {
        if (*p == '\0') finished = true;
        if (*p != delim && *p != '\0' && !(delim == '\0' && isspace(*p))) {
            continue;
        }
        int size = p - begin;
        if (size == 0) {
            begin = p + 1;
            continue;
        }
        char *buf = malloc(sizeof(char) * (size + 1));
        buf[size] = '\0';
        memcpy(buf, begin, size * sizeof(char));
        begin = p + 1;
        ret[i] = buf;
        i++;
    }
    return ret;
}

void str_list_free(char **list) {
    char **p = list;
    while (*p != NULL) {
        free(*p);
        p++;
    }
    free(list);
}

char* str_strip(char *str) {
    int len = strlen(str);
    char *begin = str;
    char *end = str + len - 1;
    while (isspace(*begin) && begin < end) {
        begin++;
    }
    while (isspace(*end) && end >= begin) {
        end--;
    }
    len = end - begin + 1;
    char *buf = malloc(sizeof(char) * (len) + 1);
    buf[len] = '\0';
    memcpy(buf, begin, len);
    return buf;
}



