#ifndef PARSING_H
#define PARSING_H
#include "user_string.h"
#include "math_defines.h"

string *GetNumberFromString(string *str, size_t *pos);
char GetOperatorFromString(string *str, size_t *pos);
string *ToPostfixForm(string *expression);
char *IsOperator(char c);
char IsUnar(const string *str, size_t pos, char op);
char FuncStingToChar(const string *func);
int IsDigitAndX(char c);

#endif