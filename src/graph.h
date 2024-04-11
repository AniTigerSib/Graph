#ifndef GRAPH_H
#define GRAPH_H
#include "user_string.h"

void Init(double **matrix);
int FinalCalc(double **matrix, string *postfix);
void Print(const double **matrix);

#endif