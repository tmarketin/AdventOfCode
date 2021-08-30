#include <stdio.h>
#include <stdlib.h>

#define NMAX 9
#define TMAX 2503

const char *names[] = {"Vixen","Blitzen","Rudolph","Cupid","Donner","Dasher","Comet","Prancer","Dancer"};
const int speed[] = {8,13,20,12,9,10,3,9,37};
const int tv[] = {8,4,7,4,5,4,37,12,1};
const int tr[] = {53,49,132,43,38,37,76,97,36};

int main() {
  int dist[NMAX];
  int points[NMAX];

  int t,i,dmax,idmax;

  for(i = 0; i < NMAX; i++) {
    dist[i] = 0;
    points[i] = 0;
  }

  for(t = 1; t <= TMAX; t++) {
    for(i = 0; i < NMAX; i++)
      if(t % (tv[i] + tr[i]) > 0 && t % (tv[i] + tr[i]) <= tv[i])
        dist[i] = dist[i] + speed[i];

    idmax = 0;
    dmax = dist[0];
    for(i = 1; i < NMAX; i++)
      if(dist[i] > dmax) {
        idmax = i;
        dmax = dist[i];
      }

    points[idmax]++;
  }

  for(i = 0; i < NMAX; i++)
    printf("%s %d %d\n",names[i],dist[i],points[i]);

  return 0;
}