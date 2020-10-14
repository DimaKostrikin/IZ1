#ifndef IZ1_UTILS_H
#define IZ1_UTILS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *read_string(FILE *stream);
int filter(const char **vect_of_strings, const int *num_of_lines, char ***res_vect);
int init(FILE *stream);

#endif //IZ1_UTILS_H
