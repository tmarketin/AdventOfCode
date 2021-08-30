#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char str[200];
  char str2[200];

  int i,j,c;
  int len,totcount;
  int c2,totcount2;

  FILE *fp;

// part 1
  totcount = 0;
  totcount2 = 0;
  fp = fopen("day8.dat","r");
  while(fgets(str,200,fp) != 0) {
    len = strlen(str);
    if(str[len-1] == '\n') 
      str[len-1] = '\0';
    len = strlen(str);

    c = 0;
    i = 1;
    strncpy(str2,"\"\\\"",3);
    j = 3;
    while(i < len - 1) {
      if(str[i] == '\\') {
        if(str[i+1] == '\"') {
          i++;
          strncpy(str2+j,"\\\\\\\"",4);
          j = j + 4;
        }
        else if(str[i+1] == '\\') {
          i++;
          strncpy(str2+j,"\\\\\\\\",4);
          j = j + 4;
        }
        else if(str[i+1] == 'x') {
          strncpy(str2+j,"\\\\",2);
          j = j + 2;
          strncpy(str2+j,str+i+1,3);
          i = i + 3;
          j = j +3;
        }
      }
      else{
        str2[j] = str[i];
        j++;
      }
      c++;

      i++;
    }
    strncpy(str2+j,"\\\"\"\0",4);
    printf("%s %s\n",str,str2);
    totcount = totcount + len - c;
    totcount2 = totcount2 + strlen(str2) - len;
  }
  fclose(fp);

  printf("Total count: %d\n",totcount);
  printf("Total count 2: %d\n",totcount2);

  return 0;
}