#include <stdio.h>
#include <stdlib.h>

#define NSTEP 100
#define NSIZE 100
#define MATSIZE NSIZE+2

void printmat(char **, int);
char **initmat(int);
char **deletemat(char **);
int countmat(char **, int);
int countchar(char **, int, int);

int main() {
  char **f = NULL;
  char **g = NULL;
  char **tmp = NULL;

  int c,count;

  FILE *fp;

  f = initmat(MATSIZE);
  g = initmat(MATSIZE);

  fp = fopen("day18.dat","r");
  count = 0;
  while((c = fgetc(fp)) != EOF) {
    if(c != '\n') {
      if(c == '.')
        f[1 + count/NSIZE][1 + (count % NSIZE)] = 0;
      else if(c == '#')
        f[1 + count/NSIZE][1 + (count % NSIZE)] = 1;
      count++;
    }
  }
  fclose(fp);
  f[1][1] = 1;
  f[1][NSIZE] = 1;
  f[NSIZE][1] = 1;
  f[NSIZE][NSIZE] = 1;

//  printf("Step: %d\n",0);
//  printmat(f,NSIZE);
  for(int iter = 1; iter <= NSTEP; iter++) {
    for(int row = 1; row <= NSIZE; row++)
      for(int col = 1; col <= NSIZE; col++) {
        if((row == 1 || row == NSIZE) && (col == 1 || col == NSIZE))
          g[row][col] = 1;
        else {
          if(f[row][col] == 1 && (countchar(f,row,col) == 2 || countchar(f,row,col) == 3))
            g[row][col] = 1;
          else if(f[row][col] == 1 && (countchar(f,row,col) < 2 || countchar(f,row,col) > 3))
            g[row][col] = 0;

          if(f[row][col] == 0 && countchar(f,row,col) == 3)
            g[row][col] = 1;
          else if(f[row][col] == 0 && countchar(f,row,col) != 3)
            g[row][col] = 0;
        }
      }

    tmp = f; f = g; g = tmp;

//    printf("Step: %d\n",iter);
//    printmat(f,NSIZE);
  }

  printf("\nFinal count: %d\n",countmat(f,NSIZE));

  f = deletemat(f);
  g = deletemat(g);

  return 0;
}

void printmat(char **f, int n) {
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++)
      printf("%d ",f[i][j]);
    printf("\n");
  }
  printf("\n");

  return;
}

char **initmat(int n) {
  char **f;

  f = (char **)malloc(n*sizeof(char *));
  f[0] = (char *)malloc(n*n*sizeof(char));
  for(int i = 1; i < n; i++)
    f[i] = f[i-1] + n;

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      f[i][j] = 0;

  return f;
}

char **deletemat(char **f) {
  free(f[0]);
  free(f);

  return NULL;
}

int countchar(char **f, int row, int col) {
  int c = 0;

  for(int i = row - 1; i <= row + 1; i++)
    for(int j = col - 1; j <= col + 1; j++)
      c = c + f[i][j];

  return c - f[row][col];
}

int countmat(char **f, int n) {
  int c = 0;

  for(int row = 1; row <= n; row++)
    for(int col = 1; col <= n; col++)
        c = c + f[row][col];

  return c;
}