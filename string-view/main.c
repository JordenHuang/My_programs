#include <stdio.h>
#include <string.h>

#define SV_IMPLEMENTATION
#include "sv.h"


int main(void) {
#if 0
    char str[] = "A quick brown fox jumps over the lazy dog";
    StringView sv_str = sv_from_cstr(str);
    StringView sub_str1 = sv_substr(sv_str, 14, 17);
    StringView sub_str2 = sv_substr(sv_str, 18, 22);
    StringView sub_str3 = sv_substr(sv_str, 14, 17);

    printf("\nThe string   : %s", str);
    printf("\nThe sv-string: ");
    sv_print(stdout, sv_str);
    printf("\nThe sub-string1: ");
    sv_print(stdout, sub_str1);
    printf("\nThe sub-string2: ");
    sv_print(stdout, sub_str2);
    printf("\nThe sub-string3: ");
    sv_print(stdout, sub_str3);
    printf("\n");

    if (sv_equal(sub_str1, sub_str2) == true) {
        printf("sub_str1 is equal to sub_str2\n");
    } else {
        printf("sub_str1 is NOT equal to sub_str2\n");
    }

    if (sv_equal(sub_str1, sub_str3) == true) {
        printf("sub_str1 is equal to sub_str3\n");
    } else {
        printf("sub_str1 is NOT equal to sub_str3\n");
    }

#else

    //  StringView sv = sv_from_cstr("Hello world");
    StringView sv = SV("Hello world");
    printf("sv is: ");
    sv_print(stdout, sv);
    printf("\n");
    printf("sv is empty? %s\n", sv_is_empty(sv) == true ? "True": "False");
    for (int i = -(sv.len); i < (int)(sv.len); ++i) {
        printf("sv at index %3d? %c\n", i, sv_at(sv, i));
    }
    printf("sv starts with [%s]? %s\n", "Hel", sv_starts_with_cstr(sv, "Hel") ? "True" : "False");
    printf("sv starts with [%s]? %s\n", "hel", sv_starts_with_cstr(sv, "hel") ? "True" : "False");

    printf("sv starts with cstr [%s]? %s\n", "Hel", sv_starts_with(sv, sv_from_cstr("Hel")) ? "True" : "False");
    printf("sv starts with cstr [%s]? %s\n", "hel", sv_starts_with(sv, sv_from_cstr("hel")) ? "True" : "False");

    #define END_STR "]\n"
    StringView sv2 = sv_from_cstr("  Trim me .  ");
    printf(       "sv2 is    : [");
    sv_print(stdout, sv2);
    printf(END_STR"Trim left : [");
    sv_print(stdout, sv_trim_left(sv2));
    printf(END_STR"Trim right: [");
    sv_print(stdout, sv_trim_right(sv2));
    printf(END_STR"Trim      : [");
    sv_print(stdout, sv_trim(sv2));
    printf(END_STR);
    #undef END_STR

#endif

    return 0;
}

void lines() {
#define A "▀"
#define B "▄"
#define C "─"

#define LINES 8
#define COLUMNS 24

    char chars[][10] = {A B C, B A C, A C B, B C A};
    size_t len = sizeof(chars) / sizeof(chars[0]);
    StringView sv_chars[len];
    for (size_t i = 0; i < len; ++i) {
        sv_chars[i] = sv_from_cstr(chars[i]);
    }

    for (size_t r = 0, i = 0; r < LINES; ++r, i = (i+1)%4) {
        for (size_t c = 0; c < COLUMNS; ++c) {
            sv_print(stdout, sv_chars[i]);
        }
        printf("\n");
    }
}
