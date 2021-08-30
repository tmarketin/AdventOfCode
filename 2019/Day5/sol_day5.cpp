#include <iostream>

#include "../Libs/intcode.h"

using std::cout;
using std::endl;

int main() {
  Intcode program("input_day5.dat");

  program.addToInput(1);
  program.executeProgram();
  cout << "Part 1: ";
  Value_t res = 1;
  do {
    res = program.getOutput();
  } while(res == 0);
  cout << res << endl;

  program.resetCode();
  program.addToInput(5);
  program.executeProgram();
  cout << "Part 2: " << program.getOutput() << endl;

  return 0;
}