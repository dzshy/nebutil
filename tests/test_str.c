#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <str.h>

void test_str_split() {
    char *s = "abc 123 233 xyz";
    char **list = str_split(s, ' ');
    assert(list[4] == NULL);
    assert(list[3] != NULL);
    assert(strcmp(list[0], "abc") == 0);
    assert(strcmp(list[3], "xyz") == 0);
    str_list_free(list);

    s = "abc  123 233 xyz";
    list = str_split(s, ' ');
    assert(list[4] == NULL);
    assert(list[3] != NULL);
    assert(strcmp(list[0], "abc") == 0);
    assert(strcmp(list[3], "xyz") == 0);
    str_list_free(list);

    s = "   abc  123 233 xyz";
    list = str_split(s, ' ');
    assert(list[4] == NULL);
    assert(list[3] != NULL);
    assert(strcmp(list[0], "abc") == 0);
    assert(strcmp(list[3], "xyz") == 0);
    str_list_free(list);

    s = "   abc \t 123\n 233\nxyz";
    list = str_split(s, '\0');
    assert(list[4] == NULL);
    assert(list[3] != NULL);
    assert(strcmp(list[0], "abc") == 0);
    assert(strcmp(list[3], "xyz") == 0);
    str_list_free(list);

    s = "a";
    list = str_split(s, ' ');
    assert(list[1] == NULL);
    assert(list[0] != NULL);
    assert(strcmp(list[0], "a") == 0);
    str_list_free(list);

    s = "";
    list = str_split(s, ' ');
    assert(list[0] == NULL);
    str_list_free(list);

    s = "  ";
    list = str_split(s, ' ');
    assert(list[0] == NULL);
    str_list_free(list);

}

void test_str_strip() {
    char *s;

    s = str_strip("hello ");
    assert(strcmp(s, "hello") == 0);

    s = str_strip("hello");
    assert(strcmp(s, "hello") == 0);

    s = str_strip("\nhello ");
    assert(strcmp(s, "hello") == 0);

    s = str_strip("\nhello");
    assert(strcmp(s, "hello") == 0);

    s = str_strip("");
    assert(strcmp(s, "") == 0);

    s = str_strip("\n\t ");
    assert(strcmp(s, "") == 0);

    s = str_strip(" ");
    assert(strcmp(s, "") == 0);
}

void test_str_bulider() {
    StrBuilder sb;
    sb_init(&sb);

    sb_append(&sb, "%s", "hello");
    assert(sb.size == 5);
    assert(strcmp(sb.buf, "hello") == 0);
    assert(strlen(sb.buf) == 5);

    sb_append(&sb, "hello");
    assert(sb.size == 10);
    assert(strcmp(sb.buf, "hellohello") == 0);

    sb_append(&sb, "%c1", 'c');
    assert(sb.size == 12);
    assert(strcmp(sb.buf, "hellohelloc1") == 0);
}

int main() {
    printf("[TEST] str\n");
    
    test_str_split();
    test_str_strip();

    printf("[PASS] str\n");
    return 0;
}
