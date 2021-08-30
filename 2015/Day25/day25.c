#include <stdio.h>

const long int mult = 252533;
const long int div = 33554393;

int main() {
  int rmax,row,col;
  long int pass = 20151125;

  for(rmax = 1; rmax < 7000; rmax++) {
    row = rmax;
    col = 1;
    while (row > 0) {
      if(row == 2981 && col == 3075) {
        printf("row: %d col: %d pass: %lu\n",row,col,pass);
        break;
      }
      pass = (pass*mult) % div;
      row--;
      col++;
    }
  }

  return 0;
}