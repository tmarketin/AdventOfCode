#include <stdio.h>
#include <stdlib.h>

#define LEN 10000

typedef struct house{
  int x,y;
  int gift;
} house;

typedef struct {
  int x,y;
} coords;

int getNumberOfVisitedHouses(int roboSantaActivated);

int main() {

  printf("Part 1 solution: %d\n", getNumberOfVisitedHouses(0));
  printf("Part 2 solution: %d\n", getNumberOfVisitedHouses(1));

  return 0;
}

int getNumberOfVisitedHouses(int roboSantaActivated) {
  char c;

  int i,select,k,last;

  house grid[LEN];
  coords santa[2];

  FILE *fp;

  grid[0].x = 0;
  grid[0].y = 0;
  grid[0].gift = 2;
  last = 0;
  santa[0].x = 0; // santa
  santa[0].y = 0;
  santa[1].x = 0; // robosanta
  santa[1].y = 0;

  fp = fopen("day3.dat","r");
  i = 0;
  while((c = fgetc(fp)) != EOF) {
    select = i % (1 + roboSantaActivated);
    i++;
    if(c == 'N')
      santa[select].y++;
    else if(c == 'S')
      santa[select].y--;
    else if(c == 'E')
      santa[select].x++;
    else 
      santa[select].x--;

    k = 0; // search if already visited
    while(k <= last) {
      if(santa[select].x == grid[k].x && santa[select].y == grid[k].y) {
        grid[k].gift++;
        break;
      }
      k++;
    }
    if(k > last) {
      last++;
      grid[last].x = santa[select].x;
      grid[last].y = santa[select].y;
      grid[last].gift = 1;
    }
  }
  fclose(fp);

  return last + 1;
}