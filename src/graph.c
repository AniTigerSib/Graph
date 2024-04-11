#include "graph.h"

#include <math.h>
#include <stdio.h>

#include "input.h"
#include "parsing.h"
#include "postfix_calc.h"
#include "user_string.h"

int main() {
    string *input = ReadInput();
    if (input == NULL) {
        printf("Empty input\n");
        return 0;
    }
    string *postfix = ToPostfixForm(input);
    if (postfix == NULL) {
        printf("Invalid input\n");
        return 0;
    }
    double *graphic = (double *)calloc(80 * 2, sizeof(double));
    double **ptr = (double **)calloc(80, sizeof(double *));
    for (int i = 0; i < 80; i++) {
        ptr[i] = &graphic[i * 2];
    }
    Init(ptr);
    FinalCalc(ptr, postfix);
    Print((const double **)ptr);
    FreeString(input);
    FreeString(postfix);
    free(ptr);
    free(graphic);
    return 0;
}

void Init(double **matrix) {
    double step = 4 * M_PI / 79;
    for (int i = 0; i < 80; i++) {
        matrix[i][0] = i * step;
        matrix[i][1] = NAN;
    }
}

int FinalCalc(double **matrix, string *postfix) {
    double step = (double)2 / 24;
    for (int i = 0; i < 80; i++) {
        double res = Calc(postfix, matrix[i][0]);
        if (isnan(res)) continue;
        res = round(res * 1000) / 1000;
        double j = -1;
        for (int k = 0; k < 25; k++) {
            if (fabs(j - res) < step) {
                matrix[i][1] = j;
            }
            j += step;
        }
    }
    return 1;
}

void Print(const double **matrix) {
    double step = (double)2 / 24;
    double i = -1;
    for (int k = 0; k < 25; k++) {
        for (int j = 0; j < 80; j++) {
            // printf("%lf \n", matrix[j][1]);
            if (isnan(matrix[j][1])) {
                printf(".");
                continue;
            }
            if (fabs(matrix[j][1] - i) < EPS) {
                printf("*");
            } else {
                printf(".");
            }
        }
        i += step;
        printf("\n");
    }
}