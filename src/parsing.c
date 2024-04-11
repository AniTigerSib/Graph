#include "parsing.h"

#include <stdio.h>
#include <string.h>

#include "stack.h"

const char operators[] = "+-*/(~";

DEFINE_STACK(char);
DEFINE_STACK_METHODS(char);

string *GetNumberFromString(string *str, size_t *pos) {
    string *res = NewString();
    while (*pos < str->len) {
        char num = str->value[*pos];
        if (IsDigitAndX(num)) {
            AddToString(res, num);
        } else {
            (*pos)--;
            break;
        }
        (*pos)++;
    }
    return res;
}

char GetOperatorFromString(string *str, size_t *pos) {
    char symbol = str->value[*pos];
    char ans_symbol = 0;
    if (IsOperator(symbol)) {
        ans_symbol = symbol;
    } else {
        string *result_string = NewString();
        while (*pos < str->len && !IsDigitAndX(symbol) && !IsOperator(symbol)) {
            AddToString(result_string, symbol);
            symbol = str->value[++(*pos)];
        }
        (*pos)--;
        ans_symbol = FuncStingToChar(result_string);
        FreeString(result_string);
    }
    return ans_symbol;
}

string *ToPostfixForm(string *expression) {
    if (expression == NULL) {
        return NULL;
    }
    string *postfix_expression = NewString();
    Stack *operators_stack = CreateStack_char();
    DeleteSpaces(expression);
    for (size_t i = 0; i < expression->len; i++) {
        char current_symbol = expression->value[i];
        if (IsDigitAndX(current_symbol)) {
            string *digit = GetNumberFromString(expression, &i);
            AddToString(digit, ' ');
            ConcatStrings(postfix_expression, digit);
            digit = NULL;
        } else if (current_symbol == '(') {
            Push_char(operators_stack, current_symbol);
        } else if (current_symbol == ')') {
            while (operators_stack->count > 0 && Peek_char(operators_stack) != '(')
                AddToString(postfix_expression, PopValue_char(operators_stack));
            PopValue_char(operators_stack);
        } else {
            char operator= GetOperatorFromString(expression, &i);
            if (operator) {
                operator= IsUnar(expression, i, operator);
                while (operators_stack->count > 0 &&
                       (Priority(Peek_char(operators_stack)) >= Priority(operator)))
                    AddToString(postfix_expression, PopValue_char(operators_stack));
                Push_char(operators_stack, operator);
            } else {
                FreeString(postfix_expression);
                FreeStack_char(&operators_stack);
                return NULL;
            }
        }
    }
    while (operators_stack->count > 0) {
        AddToString(postfix_expression, PopValue_char(operators_stack));
    }
    FreeStack_char(&operators_stack);
    return postfix_expression;
}

char *IsOperator(char c) { return strchr(operators, c); }

char IsUnar(const string *str, size_t pos, char op) {
    if (op == '-' && (pos == 0 || (pos > 1 && !IsDigitAndX(str->value[pos - 1])))) return '~';
    return op;
}

int IsDigitAndX(char c) { return (c >= '0' && c <= '9') || c == 'x'; }

char FuncStingToChar(const string *func) {
    if (!strcmp(func->value, "sin")) {
        return SIN;
    } else if (!strcmp(func->value, "cos")) {
        return COS;
    } else if (!strcmp(func->value, "tan")) {
        return TAN;
    } else if (!strcmp(func->value, "ctg")) {
        return CTG;
    } else if (!strcmp(func->value, "sqrt")) {
        return SQRT;
    } else if (!strcmp(func->value, "ln")) {
        return LN;
    }
    return '\0';
}