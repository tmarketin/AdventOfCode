#include <stdio.h>
#include <stdlib.h>

const int data[4][5] = {{3,0,0,-3,2},{-3,3,0,0,9},{-1,0,4,0,1},{0,0,-2,2,8}};

int main() {
  int i,j,k,l,m;
  int s,tmp[5];

  for(i = 1; i < 101; i++)
    for(j = 1; j < 101; j++)
      for(k = 1; k < 101; k++)
        for(l = 1; l < 101; l++)
          if(i + j + k + l == 100) {
            s = 1;
            for(m = 0; m < 5; m++) {
              tmp[m] = i*data[0][m] + j*data[1][m] + k*data[2][m] + l*data[3][m];
              if(tmp[m] < 0)
                tmp[m] = 0;
            }
            s = tmp[0]*tmp[1]*tmp[2]*tmp[3]; 
            if(tmp[4] == 500)
              printf("%d %d %d %d %d\n",i,j,k,l,s);
          }

  return 0;
}