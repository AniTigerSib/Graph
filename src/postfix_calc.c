#include "postfix_calc.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "parsing.h"
#include "user_string.h"

double Execute(char op, double a, double b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return b < EPS ? NAN : a / b;
        default:
            return 0;
    }
}

double ExecuteTrigFunc(char op, double val) {
    switch (op) {
        case SIN:
            return sin(val);
        case COS:
            return cos(val);
        case TAN:
            return fabs(fmod(val, (M_PI / 2))) < EPS ? NAN : tan(val);
        case CTG:
            return fabs(fmod(val, M_PI)) < EPS ? NAN : (1 / tan(val));
        case SQRT:
            return val > EPS ? sqrt(val) : NAN;
        case LN:
            return val > EPS ? log(val) : NAN;
        default:
            return 0;
    }
}

double ConvertStringToNumber(string *str, double current_x) {
    if (str == NULL || str->value == NULL || str->len == 0) return NAN;
    double res = 0;
    if (str->len == 1 && str->value[0] == 'x') {
        res = current_x;
    } else {
        for (int i = str->len - 1; i >= 0; i--) {
            res += (str->value[i] - '0') * pow(10, str->len - 1 - i);
        }
    }
    FreeString(str);
    return res;
}

DEFINE_STACK_METHODS(double)

double Calc(string *postfix_expression, double x) {
    Stack *locals = CreateStack_double();
    for (size_t i = 0; i < postfix_expression->len; i++) {
        char current_symbol = postfix_expression->value[i];
        if (IsDigitAndX(current_symbol)) {
            string *digit = GetNumberFromString(postfix_expression, &i);
            double val = ConvertStringToNumber(digit, x);
            Push_double(locals, val);
            digit = NULL;
        } else if (IsOperator(current_symbol)) {
            if (current_symbol == '~') {
                double last = locals->count > 0 ? PopValue_double(locals) : 0;
                Push_double(locals, Execute('-', 0, last));
                continue;
            }
            double second = locals->count > 0 ? PopValue_double(locals) : 0;
            double first = locals->count > 0 ? PopValue_double(locals) : 0;
            double res = Execute(current_symbol, first, second);
            if (!isnan(res) && res != INFINITY && res != -INFINITY) {
                Push_double(locals, res);
            } else {
                FreeStack_double(&locals);
                return NAN;
            }
        } else if (current_symbol != ' ') {
            double val = locals->count > 0 ? PopValue_double(locals) : 0;
            double res = ExecuteTrigFunc(current_symbol, val);
            if (!isnan(res) && res != INFINITY && res != -INFINITY) {
                Push_double(locals, res);
            } else {
                FreeStack_double(&locals);
                return NAN;
            }
        }
    }
    Peek_double(locals);
    double res = PopValue_double(locals);
    FreeStack_double(&locals);
    return res;
}