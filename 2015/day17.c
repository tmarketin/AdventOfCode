#include <stdio.h>

#define MAXN 20

const int size[] = {43,3,4,10,21,44,4,6,47,41,34,17,17,44,36,31,46,9,27,38};

int count;

void rec_sum(int tot, int curr, int cnt) {
  if(curr >= MAXN || tot < 0)
    return;

  if(size[curr] == tot) {
    count++;
    printf("%d\n",cnt+1);
  }
  else
    rec_sum(tot-size[curr],curr+1,cnt+1);

  if(curr + 1 < MAXN)
    rec_sum(tot,curr+1,cnt);

  return;
}

int main() {
  count = 0;

  rec_sum(150,0,0);

  printf("Count: %d\n",count);

  return 0;
}