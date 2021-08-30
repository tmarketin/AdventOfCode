#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 8

void increment(char *);
int rule1(char *);
int rule2(char *);
int rule3(char *);

int main() {
//  char pass[8] = "hepxxyzz";
  char pass[8] = "ghijklmn";

  int i = 0;

  increment(pass);
  while(! rule1(pass) || ! rule2(pass) || ! rule3(pass))
    increment(pass);

  printf("%s\n",pass);

  return 0;
}

int rule1(char *s) {
  int i,k = 0;

  for(i = 0; i < 6; i++) {
    if(s[i+1] == s[i] + 1 && s[i+2] == s[i] + 2) {
      k = 1;
      break;
    }
  }

  return k;
}

int rule2(char *s) {
  int i,k = 1;

  for(i = 0; i < LEN; i++)
    if(s[i] == 'i' || s[i] == 'o' || s[i] == 'l') {
      k = 0;
      break;
    }

  return k;
}

int rule3(char *s) {
  int i,j,k = 0;

  for(i = 0; i < LEN - 3; i++) {
    if(s[i+1] == s[i]) {
      for(j = i+2; j < LEN - 1; j++) {
        if(s[j+1] == s[j] && s[j] != s[i]) {
          k = 1;
          break;
        }
      }
    }
  }

  return k;
}

void increment(char *s) {
  int i,carry;

  i = 7;
  carry = 1;
  while(i >= 0) {
    if(s[i] == 'z') {
      s[i] = 'a';
      carry = 1;
      i--;
    }
    else {
      s[i] = s[i] + carry;
      if(s[i] == 'i' || s[i] == 'o' || s[i] == 'l')
        s[i]++;
      break;
    }
  }

  return;
}