/* Copyright (c) 2022-2023, Dzshy <dzshy@outlook.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <str.h>

void test_str_split()
{
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

void test_str_strip()
{
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

void test_str_bulider()
{
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

    sb_appendc(&sb, 'x');
    assert(sb.size == 13);
    assert(strcmp(sb.buf, "hellohelloc1x") == 0);
}

int main()
{
    printf("[TEST] str\n");

    test_str_split();
    test_str_strip();

    printf("[PASS] str\n");
    return 0;
}
