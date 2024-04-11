#include <math.h>
#include <stdio.h>

#include "input.h"
#include "parsing.h"
#include "postfix_calc.h"
#include "user_string.h"

int main() {
    string *input_string = ReadInput();
    string *parsed_string = ToPostfixForm(input_string);
    if (parsed_string != NULL) {
        double res = Calc(parsed_string, 1);
        PrintString(parsed_string);
        if (!isnan(res)) printf("%lf\n", res);
        FreeString(parsed_string);
    }
    PrintString(input_string);
    FreeString(input_string);
    return 0;
}