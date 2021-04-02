
#ifndef LANG_UTILS_H
#define LANG_UTILS_H
#include <stdlib.h>
#include <stdio.h>

int **create2dArray(int m, int n);
void destory2dArray(int **arr);
void destoryArray(int *arr);
void print2dArray(int **arr, int row, int col);

#endif