#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "../Libs/intcode.h"

using std::cout;
using std::endl;

int main() {
  Intcode program("input_day9.dat");

  program.addToInput(1);
  program.executeProgram();
  cout << "Part 1: " << program.getOutput() << endl;

  program.resetCode();
  program.addToInput(2);
  program.executeProgram();
  cout << "Part 2: " << program.getOutput() << endl;

  return 0;
}