#include <stdio.h>
#include <stdlib.h>

#define ALEN 4

void genperm(int, int *);
void printarray(int, int *);

int main() {
  int a[] = {1,2,3,4};

  genperm(ALEN,a);

  return 0;
}

void genperm(int n, int *a)
{
  int tmp;
  int c,s;
  
  if(n == 1)
    printarray(ALEN,a);
  else
  {
    for(c = 1; c <= n; c++)
    {
      genperm(n-1,a);
      
      if(n%2 == 1)
        s = 0;
      else
        s = c - 1;
      
      tmp = a[n-1];
      a[n-1] = a[s];
      a[s] = tmp;
    }
  }
}


void printarray(int n, int *a) {
  int i;

  for(i = 0; i < n; i++)
    printf("%d ",a[i]);
  printf("\n");

  return;
}