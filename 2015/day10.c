#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 50
#define MAXLEN 10000000

const char init_string[]="1321131112";

int main() {
  char *str,*str2;
  char strint[100];
  char *ps;
  char tmpc;

  int i,j,k;
  int len;

  str = (char *)malloc(MAXLEN*sizeof(char));
  str2 = (char *)malloc(MAXLEN*sizeof(char));

  strcpy(str,init_string);
  strcpy(str2,"");

  for(i = 0; i < NMAX; i++) {
    len = strlen(str);
    j = 0;
    ps = str2;
    while(j < len) {
      tmpc = str[j];
      k = 1;
      while(str[j+k] == str[j])
        k++;
      sprintf(strint,"%d",k);
      sprintf(ps,"%d",k);
      ps = ps + strlen(strint);
      *ps = tmpc;
      ps++;
      j = j + k;
    }
    strcpy(str,str2);
    printf("i: %d, %d\n",i,strlen(str));
  }
  printf("Final: %d\n",strlen(str));

  return 0;
}