#include <stdio.h>
#include <stdlib.h>

#define NMAX 1000
#define NMAX2 NMAX*NMAX

// 1 - turn on
// 0 - turn off
// 2 - toggle

void turnon(char *, int, int, int, int);
void turnoff(char *, int, int, int, int);
void toggle(char *, int, int, int, int);

int main() {
  char *field;

  int i,c;
  int funk,x1,y1,x2,y2;

  FILE *fp;

  field = (char *)malloc(NMAX2*sizeof(char));

  for(i = 0; i < NMAX*NMAX; i++)
    *(field + i) = 0;

  fp = fopen("day6.dat","r");
  while(fscanf(fp,"%d %d %d %d %d\n",&funk,&x1,&y1,&x2,&y2) != EOF) {
    if(funk == 1)
      turnon(field,x1,y1,x2,y2);
    else if(funk == 2)
      toggle(field,x1,y1,x2,y2);
    else
      turnoff(field,x1,y1,x2,y2);
  }

  c = 0;
  for(i = 0; i < NMAX2; i++)
    c = c + *(field + i);

  printf("Total: %d\n",c);

  return 0;
}

void turnon(char *f, int x1, int y1, int x2, int y2) {
  int i,j,k;

  for(i = x1; i <= x2; i++)
    for(j = y1; j <= y2; j++) {
      k = j*NMAX + i;
      *(f + k) = *(f + k) + 1;
    }

  return;
}

void turnoff(char *f, int x1, int y1, int x2, int y2) {
  int i,j,k;

  for(i = x1; i <= x2; i++)
    for(j = y1; j <= y2; j++) {
      k = j*NMAX + i;
      if(*(f + k) > 0)
        *(f + k) = *(f + k) - 1;
    }

  return;
}

void toggle(char *f, int x1, int y1, int x2, int y2) {
  int i,j,k;

  for(i = x1; i <= x2; i++)
    for(j = y1; j <= y2; j++) {
      k = j*NMAX + i;
      *(f + k) = *(f + k) + 2;
    }

  return;
}
