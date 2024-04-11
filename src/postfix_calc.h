#ifndef POSTFIX_CALC_H
#define POSTFIX_CALC_H

#define M_PI 3.14159265358979323846
#define EPS 1e-6f

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define X_MIN 0
#define Y_MIN -1
#define X_MAX 4 * M_PI
#define Y_MAX 1

#include "stack.h"
#include "math_defines.h"
#include "user_string.h"

DEFINE_STACK(double)

double Execute(char op, double a, double b);
double ExecuteTrigFunc(char op, double val);
double ConvertStringToNumber(string *str, double current_x);
double Calc(string *postfix_expression, double x);

#endif