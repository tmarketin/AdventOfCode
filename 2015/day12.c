#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 40000

int main() {
  char str[MAXLEN];

  int len,i,j,k,c;

  fgets(str,40000,stdin);
  len = strlen(str);

  i = 0;
  while (i < len) {
    if(str[i] == 'r' && str[i+1] == 'e' && str[i+2] == 'd') {
      j = i;
      c = 0;
      while(j > 0) {
        if(c == 0 && (str[j] == '[' || str[j] == '{'))
          break;
        if(str[j] == ']' || str[j] == '}')
          c++;
        if(str[j] == '[' || str[j] == '{')
          c--;
        j--;
      }

      if(str[j] == '{') {
        k = i;
        c = 1;
        while(c > 0) {
          k++;
          if(str[k] == '{')
            c++;
          if(str[k] == '}')
            c--;
        }
        
        c = j+1;
        while(c < k) {
          str[c] = ' ';
          c++;
        }
        i = k - 1;
      }
    }
    i++;
  }

  printf("%s\n",str);

  return 0;
}