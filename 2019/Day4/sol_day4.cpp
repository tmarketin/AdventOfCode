#include <cstdint>
#include <iostream>
#include <vector>

#define MINVAL 367479
#define MAXVAL 893698

using std::cout;
using std::endl;

class Number {
public:
  uint8_t len;
  std::vector<uint16_t> num;
  uint32_t minValue;
  uint32_t maxValue;

  Number(uint32_t min, uint32_t max) : minValue(min), maxValue(max) {
    len = 0;
    auto iter = num.begin();
    while (min > 0) {
      iter = num.insert(iter, static_cast<uint16_t>(min % 10));
      min /= 10;
      len++;
    }
  }

  void reset() {
    num.clear();
    uint32_t min = minValue;
    auto iter = num.begin();
    while (min > 0) {
      iter = num.insert(iter, static_cast<uint16_t>(min % 10));
      min /= 10;
    }
  }

  bool passCheck() {
    bool doubleVal = false;
    bool dec = true;
    for(size_t idx = 0; idx < len - 1; idx++) {
      if(num[idx] == num[idx + 1])
        doubleVal = true;
      if(num[idx] > num[idx + 1])
        dec = false;
    }

    return (doubleVal && dec);
  }

  bool passCheck2() {
    bool doubleVal = false;
    bool dec = true;
    for(size_t idx = 0; idx < len - 1; idx++) {
      if((num[idx] == num[idx + 1]) && (idx == 0 ? true : num[idx] != num[idx - 1]) && (idx == len - 2 ? true : num[idx + 1] != num[idx + 2]))
        doubleVal = true;
      if(num[idx] > num[idx + 1])
        dec = false;
    }

    return (doubleVal && dec);
  }

  void increment() {
    size_t idx = len - 1;
    num[idx]++;
    while(num[idx] == 10) {
      num[idx] = 0;
      idx--;
      num[idx]++;
    }

    return;
  }

  void print() {
    for(auto k: num)
      cout << k << " ";
    cout << endl;

    return;
  }
};

uint32_t part1(Number & num);
uint32_t part2(Number & num);

int main() {
  Number value(MINVAL, MAXVAL);
  
  cout << "Part 1: " << part1(value) << endl;
  value.reset();

  cout << "Part 2: " << part2(value) << endl;

  return 0;
}

uint32_t part1(Number & num) {
  uint32_t res = 0;

  for(uint32_t idx = MINVAL; idx <= MAXVAL; ++idx) {
    if(num.passCheck())
      res++;
    num.increment();
  }

  return res;
}

uint32_t part2(Number & num) {
  uint32_t res = 0;

  for(uint32_t idx = MINVAL; idx <= MAXVAL; ++idx) {
    if(num.passCheck2())
      res++;
    num.increment();
  }

  return res;
}