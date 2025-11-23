#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* str;
    size_t len;
    size_t cap;
} String;

size_t str_len(const char* s) {
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

String* str_create(const char* s) {
    size_t l = str_len(s);
    String* st = (String*)malloc(sizeof(String));
    st->cap = l + 1;
    st->len = l;
    st->str = (char*)malloc(st->cap);
    for (size_t i = 0; i <= l; i++) st->str[i] = s[i];
    return st;
}

int str_append(String* st, const char* s) {
    size_t l = str_len(s);
    size_t new_len = st->len + l;

    if (new_len + 1 > st->cap) {
        size_t new_cap = (new_len + 1) * 2;
        char* temp = (char*)realloc(st->str, new_cap);
        if (!temp) return 0;
        st->str = temp;
        st->cap = new_cap;
    }

    for (size_t i = 0; i <= l; i++)
        st->str[st->len + i] = s[i];

    st->len = new_len;
    return 1;
}

void str_free(String* st) {
    free(st->str);
    free(st);
}

int main() {
    String* s = str_create("A");
    printf("Start len=%zu, cap=%zu\n", s->len, s->cap);

    str_append(s, "ABCABCABCABCABCABCABCABCABC");
    printf("After append len=%zu, cap=%zu\n", s->len, s->cap);

    for (int i = 0; i < 5; i++) {
        str_append(s, "1234567890");
        printf("After loop %d: len=%zu, cap=%zu\n", i+1, s->len, s->cap);
    }

    printf("Result: %s\n", s->str);
    str_free(s);
    return 0;
}
