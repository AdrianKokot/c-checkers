#include "../headers/lang_utils.h"

int **create2dArray(int row, int col)
{
  int **arr = (int **)malloc(row * sizeof(int *));

  for (int i = 0; i < row; i++)
  {
    arr[i] = (int *)malloc(col * sizeof(int));
    for (int j = 0; j < col; j++)
    {
      arr[i][j] = 0;
    }
  }

  return arr;
}

void destory2dArray(int **arr)
{
  free(*arr);
  free(arr);
}

void destoryArray(int *arr)
{
  free(arr);
}

void print2dArray(int **arr, int row, int col)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
}