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

int main() {
    printf("[TEST] str\n");
    
    test_str_split();

    printf("[PASS] str\n");
    return 0;
}
