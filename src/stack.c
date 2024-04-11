#include "stack.h"

int Priority(char symbol) {
    switch (symbol) {
        case 's':
        case 'c':
        case 't':
        case 'g':
        case 'q':
        case 'l':
            return 5;
        case '~':
            return 4;
        case '*':
        case '/':
            return 3;
        case '-':
        case '+':
            return 2;
        case '(':
            return 1;
    }
    return 0;
}