#ifndef _SV_H_
#define _SV_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t len;
} StringView;

#define SV(cstr) sv_from_cstr(cstr)

StringView sv_from_cstr(const char *cstr); /* Convert c string to String View */
char *sv_to_cstr(StringView sv); /* The returned pointer needs to be freed manually */
void sv_print(FILE *stream, StringView sv); /* Print out the content of sv to stream */

bool sv_is_empty(StringView sv); /* Check if the length of sv is 0 */

char sv_at(StringView sv, int index); /* range: [0, sv.len), -1 is be the last char, -2 is the second last char, and so on */
bool sv_equal(StringView a, StringView b); /* Check if two sv, a and b, are equal or not */
bool sv_starts_with(StringView sv, StringView target); /* Check if sv starts with c string (target) or not */
bool sv_starts_with_cstr(StringView sv, const char *target); /* Check if sv starts with c string (target) or not */

StringView sv_trim_left(StringView sv); /* Trim whitespaces in the beginning */
StringView sv_trim_right(StringView sv); /* Trim whitespaces at the end */
StringView sv_trim(StringView sv); /* Trim whitespaces in the beginning and at the end */
StringView sv_substr(StringView sv, size_t begin, size_t end); /* Sub-string of sv of range [begin, end) */

#ifdef SV_IMPLEMENTATION

StringView sv_from_cstr(const char *cstr) {
    return (StringView) {
        .data = cstr,
        .len = strlen(cstr)
    };
}

char *sv_to_cstr(StringView sv) {
    char *cstr = malloc(sv.len + 1);
    for (size_t i = 0; i < sv.len; ++i) cstr[i] = sv.data[i];
    cstr[sv.len] = '\0';
    return cstr;
}

void sv_print(FILE *stream, StringView sv) {
    for (size_t i = 0; i < sv.len; ++i) {
        fprintf(stream, "%c", sv.data[i]);
    }
}

bool sv_is_empty(StringView sv) {
    return (sv.len == 0);
}

char sv_at(StringView sv, int index) {
    return sv.data[(index + sv.len) % sv.len];
}

bool sv_starts_with(StringView sv,StringView target) {
    sv = sv_substr(sv, 0, target.len);
    return sv_equal(sv, target);
}

bool sv_starts_with_cstr(StringView sv, const char *target) {
    StringView a = sv_from_cstr(target);
    sv = sv_substr(sv, 0, a.len);
    return sv_equal(sv, a);
}

bool sv_equal(StringView a, StringView b) {
    if (a.len != b.len) return false;
    for (size_t i = 0; i < a.len; ++i) {
        if (a.data[i] != b.data[i]) return false;
    }
    return true;
}

StringView sv_trim_left(StringView sv) {
    while (!sv_is_empty(sv) && sv_at(sv, 0) == ' ') {
        sv.data = sv.data + 1;
        sv.len -= 1;
    }
    return sv;
}

StringView sv_trim_right(StringView sv) {
    while (!sv_is_empty(sv) && sv_at(sv, -1) == ' ') {
        sv.len -= 1;
    }
    return sv;
}

StringView sv_trim(StringView sv) {
    return sv_trim_left(sv_trim_right(sv));
}

StringView sv_substr(StringView sv, size_t begin, size_t end) {
    StringView new_sv = {0};
    new_sv.data = sv.data + begin;
    new_sv.len = end - begin;
    return new_sv;
}

#endif // SV_IMPLEMENTATION

#endif // _SV_H_
