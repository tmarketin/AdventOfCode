#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>

using std::cout;
using std::endl;

class WireStatus {
public:
  bool redWire;
  uint32_t redWireSteps;
  bool greenWire;
  uint32_t greenWireSteps;

  WireStatus(bool red, uint32_t redS, bool green, uint32_t greenS) : redWire(red), redWireSteps(redS), greenWire(green), greenWireSteps(greenS) {
  }

  void print() {
    cout << "redWire here: " << redWire << ", steps: " << redWireSteps << endl;
    cout << "greenWire here: " << greenWire << ", steps: " << greenWireSteps << endl;
  }
};

typedef std::pair<uint8_t, uint32_t> Direction_t;
typedef std::pair<int32_t, int32_t> Coords_t;
typedef std::map<Coords_t, WireStatus> WireMap_t;

void readInput(std::string fname, WireMap_t & inputData);
void printWireMap(const WireMap_t & inputData);

uint32_t part1(const WireMap_t & data);
uint32_t part2(const WireMap_t & data);

int main() {
  WireMap_t data;

  readInput("input_day3.dat", data);

  cout << "Part 1 : " << part1(data) << endl;
  cout << "Part 2 : " << part2(data) << endl;

  return 0;
}

uint32_t part1(const WireMap_t & data) {
  uint32_t res = 0;

  for(auto k: data) {
    if(k.second.redWire && k.second.greenWire) {
      uint32_t tmpDist = abs(k.first.first) + abs(k.first.second);
      if(res == 0)
        res = tmpDist;
      else if(tmpDist < res)
        res = tmpDist;
    }
  }

  return res;
}

uint32_t part2(const WireMap_t & data) {
  uint32_t res = 0;

  for(auto k: data) {
    if(k.second.redWire && k.second.greenWire) {
      uint32_t tmpDist = k.second.redWireSteps + k.second.greenWireSteps;
      if(res == 0)
        res = tmpDist;
      else if(tmpDist < res)
        res = tmpDist;
    }
  }
  return res;
}

void readInput(std::string fname, WireMap_t & inputData) {
  std::fstream infile(fname);

  std::string line;
  uint8_t wireIdx = 0;
  while(std::getline(infile, line)) {
    Coords_t pos = std::make_pair(0, 0);
    uint32_t stepDist = 0;

    std::istringstream iss(line);
    std::string shortline;
    while(std::getline(iss, shortline, ',')) {
      char direction = shortline[0];
      uint32_t dist = std::stoi(shortline.substr(1));
      for(size_t loopIdx = 0; loopIdx < dist; loopIdx++) {
        switch(direction) {
          case 'R':
            pos.first++;
            break;
          case 'U':
            pos.second++;
            break;
          case 'L':
            pos.first--;
            break;
          case 'D':
            pos.second--;
            break;
          default:
            cout << "Error in direction! " << endl;
            break;
        }
        stepDist++;
        auto searchRes = inputData.find(pos);
        if(searchRes == inputData.end()) {
          if(wireIdx == 0) {
            inputData.insert(std::make_pair(pos, WireStatus(true, stepDist, false, 0)));
          }
          else {
            inputData.insert(std::make_pair(pos, WireStatus(false, 0, true, stepDist)));
          }
        }
        else {
          if(wireIdx == 1 && searchRes->second.greenWire == false) {
            searchRes->second.greenWire = true;
            searchRes->second.greenWireSteps = stepDist;
          }
        }
      }
    }
    wireIdx++;
  }

  return;
}

void printWireMap(const WireMap_t & inputData) {
  for(auto k: inputData)
    cout << k.first.first << ", " << k.first.second << " : " << k.second.redWire << " " << k.second.redWireSteps << " - " << k.second.greenWire << " " << k.second.greenWireSteps << endl;

  return;
}