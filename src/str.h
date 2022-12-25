#ifndef NEBUTIL_STR_H_
#define NEBUTIL_STR_H_

typedef struct {
    char *buf;
    int size;
    int cap;
} StrBuilder;

char** str_split(char *str, char delim);
void str_list_free(char **list);

char* str_strip(char *str);
char* str_add(char *a, char *b);

void sb_init(StrBuilder *sb);
void sb_appends(StrBuilder *sb, char *s);
void sb_appendc(StrBuilder *sb, char c);
void sb_appendf(StrBuilder *sb, char *format, ...);

#endif

