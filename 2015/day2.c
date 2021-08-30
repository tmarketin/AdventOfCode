#include <stdio.h>
#include <stdlib.h>

int min(int, int, int);

int main() {
  FILE *fp;

  int a,b,c;
  int s1,s2,s3;
  int tarea = 0;
  int tribbon = 0;
  int area,ribbon;

  fp = fopen("day2.dat","r");

  while(fscanf(fp,"%d %d %d",&a,&b,&c) != EOF) {
    s1 = a*b;
    s2 = a*c;
    s3 = b*c;
    area = 2*s1 + 2*s2 + 2*s3 + min(s1,s2,s3);
    tarea = tarea + area;

    s1 = 2*a + 2*b;
    s2 = 2*a + 2*c;
    s3 = 2*b + 2*c;
    ribbon = min(s1,s2,s3) + a*b*c;
    tribbon = tribbon + ribbon;
  }

  printf("Total paper area: %d\nTotal ribbon: %d\n",tarea,tribbon);

  fclose(fp);

  return 0;
}

int min(int a, int b, int c) {
  if(a < b)
    if(a < c)
      return a;
    else 
      return c;
  else
    if(b < c)
      return b;
    else
      return c;
}