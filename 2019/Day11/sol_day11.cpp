#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <set>
#include <utility>

#include "../Libs/intcode.h"

using std::cout;
using std::endl;

typedef std::pair<int32_t, int32_t> Coords_t;

class Robot {
public:
  std::set<Coords_t> paintedPlates;
  std::map<Coords_t, uint32_t> paintedMap;

  Coords_t pos = std::make_pair(0, 0);
  uint32_t dir = 0;

  Intcode * program;

  Robot(std::string fname) {
    program = new Intcode(fname);

    pos = std::make_pair(0, 0);
  }

  void changePos(uint32_t & dir, int32_t rotDir) {
    if(rotDir == 1) {
      dir = (dir + 1) % 4;
    }
    else {
      dir--;
      if(dir == -1)
        dir = 3;
    }

    switch(dir) {
      case 0:
        pos.second++;
        break;
      case 1:
        pos.first++;
        break;
      case 2:
        pos.second--;
        break;
      case 3:
        pos.first--;
        break;
    }

    return;
  }

  void reset() {
    program->resetCode();
    paintedPlates.clear();
    paintedMap.clear();

    pos = std::make_pair(0, 0);
    paintedMap[pos] = 1;

    return;
  }

  void runRobot() {
    program->addToInput(paintedMap[pos]);
    do {
      program->executeProgram();
      int32_t color = program->getOutput();
      int32_t dirChange = program->getOutput();

      paintedPlates.insert(pos);
      paintedMap[pos] = color;

      changePos(dir, dirChange);

      if(paintedMap.find(pos) != paintedMap.end())
        program->addToInput(paintedMap[pos]);
      else
        program->addToInput(0);

    } while(! program->isExecutionFinished());

    return;
  }

  void printMap() {
    int32_t min_x = 0;
    int32_t min_y = 0;
    int32_t max_x = 0;
    int32_t max_y = 0;

    for(auto k: paintedMap) {
      if(k.first.first < min_x)
        min_x = k.first.first;
      if(k.first.first > max_x)
        max_x = k.first.first;
      if(k.first.second < min_y)
        min_y = k.first.second;
      if(k.first.second > max_y)
        max_y = k.first.second;
    }

    for(int32_t idx_y = max_y; idx_y >= min_y; idx_y--) {
      for(int32_t idx_x = min_x; idx_x <= max_x; idx_x++) {
        if(paintedMap[std::make_pair(idx_x, idx_y)] == 0)
          cout << ' ';
        else
          cout << '#';
      }
      cout << endl;
    }
      
  }

  int32_t part1() {
    paintedMap[pos] = 0;
    runRobot();

    return paintedPlates.size();
  }

  void part2() {
    paintedMap[pos] = 1;
    runRobot();

    printMap();

    return;
  }
};

int main() {
  Robot robot("input_day11.dat");

  cout << "Part 1: " << robot.part1() << endl;

  robot.reset();
  cout << "Part 2: " << endl;
  robot.part2();

  return 0;
}
