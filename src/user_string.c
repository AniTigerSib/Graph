#include "user_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string *NewString() {
    string *s = NULL;
    s = (string *)malloc(sizeof(string));
    if (s == NULL) {
        return NULL;
    }
    memset(s, 0, sizeof(string));
    s->len = 0;
    s->value = (char *)calloc(1, sizeof(char));
    return s;
}

string *AddToString(string *current_str, char symbol) {
    if (current_str == NULL) {
        return NULL;
    }
    if (symbol != '\0') {
        if (current_str->value == NULL) {
            current_str->value = (char *)calloc(2, sizeof(char));
        } else {
            current_str->value = (char *)realloc(current_str->value, (current_str->len + 2) * sizeof(char));
        }
        if (current_str->value == NULL) {
            return NULL;
        }
        current_str->value[current_str->len] = symbol;
        current_str->len++;
        current_str->value[current_str->len] = '\0';
    }
    return current_str;
}

string *ConcatStrings(string *current_str, string *to_concat_str) {
    if (current_str == NULL || to_concat_str == NULL) {
        return NULL;
    }
    current_str->len = current_str->len + to_concat_str->len;
    current_str->value =
        (char *)realloc(current_str->value, (current_str->len + to_concat_str->len + 1) * sizeof(char));
    strcat(current_str->value, to_concat_str->value);
    current_str->value[current_str->len] = '\0';
    FreeString(to_concat_str);
    return current_str;
}

void PrintString(const string *str) {
    if (str == NULL || str->value == NULL) {
        return;
    }
    printf("'%s'\n", str->value);
}

void DeleteSpaces(string *str) {
    if (str == NULL || str->value == NULL) {
        return;
    }
    char *str_to_work = str->value;
    for (size_t i = 0; i < str->len; i++) {
        if (str_to_work[i] == ' ') {
            for (size_t j = i; j < str->len - 1; j++) {
                Swap(str_to_work + j, str_to_work + j + 1);
            }
            str->value = (char *)realloc(str->value, (str->len) * sizeof(char));
            str->len--;
            i--;
        }
    }
}

void FreeString(string *str) {
    if (str == NULL) {
        return;
    }
    if (str->value) {
        free(str->value);
    }
    free(str);
}

void Swap(char *val_1, char *val_2) {
    char buff = *val_1;
    *val_1 = *val_2;
    *val_2 = buff;
}