#ifndef USER_STRING_H
#define USER_STRING_H

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

typedef struct string {
    char *value;
    size_t len;
} string;

string *NewString();
string *AddToString(string *current_str, char symbol);
string *ConcatStrings(string *current_str, string *to_concat_str);
void DeleteSpaces(string *str);
void PrintString(const string *str);
void FreeString(string *str);

void Swap(char *val_1, char *val_2);

#endif