#include <stdio.h>
#include <stdlib.h>

#define NMAX 1000
#define STRLEN 16

int rule1(char *);
int rule2(char *);
int rule3(char *);
int rule4(char *);
int rule5(char *);

int main() {

  char str[17];
  char *cp;

  int i,j,count;

  FILE *fp;

  fp = fopen("day5.dat","r");
  count = 0;
  for(i = 0; i < NMAX; i++) {
    fscanf(fp,"%s",str);
//    printf("%s %d %d\n",str,rule4(str),rule5(str));
//    if(rule1(str) && rule2(str) && rule3(str))
    if(rule4(str) && rule5(str))
      count++;
  }
  printf("Total nice: %d\n",count);

  return 0;
}

int rule1(char *s) {
  int i,count;

  count = 0;
  for(i = 0; i < STRLEN; i++) {
    if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
      count++;
  }

  if(count < 3)
    return 0;
  else
    return 1;
}

int rule2(char *s) {
  int i,c;

  c = 0;
  for(i = 0; i < STRLEN - 1; i++) {
    if(s[i] == s[i+1]) {
      c = 1;
      break;
    }
  }

  if(c == 1)
    return 1;
  else
    return 0;
}

int rule3(char *s) {
  int i,c;

  c = 0;
  for(i = 0; i < STRLEN - 1; i++) {
    if((s[i] == 'a' && s[i+1] == 'b') || (s[i] == 'c' && s[i+1] == 'd') || (s[i] == 'p' && s[i+1] == 'q') || (s[i] == 'x' && s[i+1] == 'y')) {
      c = 1;
      break;
    }
  }

  if(c == 1)
    return 0;
  else
    return 1;
}

int rule4(char *s) {
  int i,j,c;

  c = 0;
  for(i = 0; i < STRLEN - 3; i++) {
    for(j = i+2; j < STRLEN - 1; j++)
      if(s[j] == s[i] && s[j+1] == s[i+1]) {
        c = 1;
        return c;
      }
  }
  return c;
}

int rule5(char *s) {
  int i;

  for(i = 0; i < STRLEN - 2; i++)
    if(s[i] == s[i+2])
      return 1;

  return 0;
}