#include <iostream>

#include "../Libs/intcode.h"

using std::cout;
using std::endl;

int32_t part1(Intcode & program);
int32_t part2(Intcode & program);

int main() {
  Intcode program("input_day2.dat");

  cout << "Part 1: " << part1(program) << endl;
  cout << "Part 2: " << part2(program) << endl;
  return 0;
}

int32_t part1(Intcode & program) {
  program.setCode(1, 12);
  program.setCode(2, 2);
  program.executeProgram();

  return program.getValue(0);
}

int32_t part2(Intcode & program) {
  for(int32_t noun = 0; noun <= 99; noun++) {
    for(int32_t verb = 0; verb <= 99; verb++) {
      program.resetCode();
      program.setCode(1, noun);
      program.setCode(2, verb);
      program.executeProgram();
      if(program.getValue(0) == 19690720)
        return 100*noun + verb;
    }
  }

  return 0;
}