#include "input.h"

#include <stdio.h>

string *ReadInput() {
    string *line = NewString();
    char c = 0;
    while (c = getchar(), c != '\n') {
        AddToString(line, c);
    }
    if (line->len == 0) {
        FreeString(line);
        return NULL;
    }
    return line;
}