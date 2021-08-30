#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

typedef int32_t Coord_t;
typedef std::array<Coord_t, 3> Coords_t;
typedef std::array<Coord_t, 3> Velocity_t;

class Moon {
public:
  Coords_t pos;
  Velocity_t vel;

  uint32_t kineticEnergy;
  uint32_t potentialEnergy;
  uint32_t totalEnergy;

  Moon(Coord_t x, Coord_t y, Coord_t z) {
    pos = {x, y, z};
    vel = {0, 0, 0};

    kineticEnergy = 0;
    potentialEnergy = abs(pos[0]) + abs(pos[1]) + abs(pos[2]);
    totalEnergy = kineticEnergy + potentialEnergy;

    return;
  }

  void updateVelocities(int32_t dvx, int32_t dvy, int32_t dvz) {
    vel[0] += dvx;
    vel[1] += dvy;
    vel[2] += dvz;

    return;
  }

  void updatePositions() {
    pos[0] += vel[0];
    pos[1] += vel[1];
    pos[2] += vel[2];

    return;
  }

  void updateEnergy() {
    kineticEnergy = abs(vel[0]) + abs(vel[1]) + abs(vel[2]);
    potentialEnergy= abs(pos[0]) + abs(pos[1]) + abs(pos[2]);

    totalEnergy = kineticEnergy*potentialEnergy;

    return;
  }

  void printStatus() {
    cout << "r = (" << pos[0] << ", "  << pos[1] << ", " << pos[2] << ")";
    cout << "     v = (" << vel[0] << ", "  << vel[1] << ", " << vel[2] << ")" << endl;

    return;
  }

  friend bool operator== (const Moon & lhs, const Moon & rhs);

};

bool operator== (const Moon & lhs, const Moon & rhs) {
  bool posEq = (lhs.pos[0] == rhs.pos[0]) && (lhs.pos[1] == rhs.pos[1]) && (lhs.pos[2] == rhs.pos[2]);
  bool velEq = (lhs.vel[0] == rhs.vel[0]) && (lhs.vel[1] == rhs.vel[1]) && (lhs.vel[2] == rhs.vel[2]);
  bool energyEq = (lhs.kineticEnergy == rhs.kineticEnergy) && (lhs.potentialEnergy == rhs.potentialEnergy) && (lhs.totalEnergy == rhs.totalEnergy);

  return posEq && velEq && energyEq;
}

typedef std::vector<Moon> MoonVec_t;

class MoonSystem {
public:
  MoonVec_t moons;
  size_t moonCount;

  uint32_t totalEnergy;

  MoonSystem(std::string) {
    std::ifstream infile("input_day12.dat");

    std::string line;
    std::regex re("[xyz<>,=]");
    while(std::getline(infile, line)) {
      std::string clean_line = std::regex_replace(line, re, "");

      std::istringstream iss(clean_line);

      size_t tmpIdx = 0;
      std::string shortline;
      std::array<Coord_t, 3> tmpPos = {0, 0, 0};
      while(std::getline(iss, shortline, ' '))
        tmpPos[tmpIdx++] = std::stoi(shortline);
      
      moons.push_back(Moon(tmpPos[0], tmpPos[1], tmpPos[2]));
    }

    moonCount = moons.size();

    totalEnergy = 0;
    for(auto moon: moons)
      totalEnergy += moon.totalEnergy;

    return;
  }

  void printSystem() {
    for(auto iter = moons.begin(); iter != moons.end(); iter++) {
      iter->printStatus();
    }
    cout << "Total energy: " << totalEnergy << endl << endl;

    return;
  }

  void updateVelocities() {
    for(size_t moon1 = 0; moon1 < moonCount - 1; moon1++) {
      for(size_t moon2 = moon1 + 1; moon2 < moonCount; moon2++) {
        int32_t dvx1 = 0;
        int32_t dvx2 = 0;
        int32_t dvy1 = 0;
        int32_t dvy2 = 0;
        int32_t dvz1 = 0;
        int32_t dvz2 = 0;

        if(moons[moon1].pos[0] < moons[moon2].pos[0]) {
          dvx1 = +1;
          dvx2 = -1;
        }
        else if(moons[moon1].pos[0] > moons[moon2].pos[0]) {
          dvx1 = -1;
          dvx2 = +1;
        }

        if(moons[moon1].pos[1] < moons[moon2].pos[1]) {
          dvy1 = +1;
          dvy2 = -1;
        }
        else if(moons[moon1].pos[1] > moons[moon2].pos[1]) {
          dvy1 = -1;
          dvy2 = +1;
        }

        if(moons[moon1].pos[2] < moons[moon2].pos[2]) {
          dvz1 = +1;
          dvz2 = -1;
        }
        else if(moons[moon1].pos[2] > moons[moon2].pos[2]) {
          dvz1 = -1;
          dvz2 = +1;
        }

        moons[moon1].updateVelocities(dvx1, dvy1, dvz1);
        moons[moon2].updateVelocities(dvx2, dvy2, dvz2);
      }
    }

    return;
  }

  void updatePositions() {
    for(auto & moon: moons)
      moon.updatePositions();
    
    return;
  }

  void updateEnergy() {
    totalEnergy = 0;
    for(auto & moon: moons) {
      moon.updateEnergy();
      totalEnergy += moon.totalEnergy;
    }

    return;
  }

  void iterateSystem() {
    updateVelocities();
    updatePositions();
    updateEnergy();

    return;
  }

  uint32_t part1(size_t iterCount) {
    for(size_t idx = 1; idx <= iterCount; idx++) {
      iterateSystem();
    }
    
    return totalEnergy;
  }

  int32_t part2(size_t iterCount) {
    std::array<uint32_t, 4> iterToRepeat = {0, 0, 0, 0};
    std::array<std::vector<Moon>, 4> moonHistory;
    moonHistory[0].push_back(moons[0]);
    moonHistory[1].push_back(moons[1]);
    moonHistory[2].push_back(moons[2]);
    moonHistory[3].push_back(moons[3]);

    for(size_t idx = 1; idx <= iterCount; idx++) {
      iterateSystem();
      auto searchRes = std::find(moonHistory[0].begin(), moonHistory[0].end(), moons[0]);
      if((searchRes != moonHistory[0].end()) && (iterToRepeat[0] == 0)) {
        cout << "Moon 1 found after " << moonHistory[0].size() << " iterations." << endl;
        iterToRepeat[0] = std::distance(searchRes, moonHistory[0].end());
      }
      else {
        moonHistory[0].push_back(moons[0]);
      }

      searchRes = std::find(moonHistory[1].begin(), moonHistory[1].end(), moons[1]);
      if((searchRes != moonHistory[1].end()) && (iterToRepeat[1] == 0)) {
        cout << "Moon 2 found after " << moonHistory[1].size() << " iterations." << endl;
        iterToRepeat[1] = std::distance(searchRes, moonHistory[1].end());
      }
      else {
        moonHistory[1].push_back(moons[1]);
      }

      searchRes = std::find(moonHistory[2].begin(), moonHistory[2].end(), moons[2]);
      if((searchRes != moonHistory[2].end()) && (iterToRepeat[2] == 0)) {
        cout << "Moon 3 found after " << moonHistory[2].size() << " iterations." << endl;
        iterToRepeat[2] = std::distance(searchRes, moonHistory[2].end());
      }
      else {
        moonHistory[2].push_back(moons[2]);
      }

      searchRes = std::find(moonHistory[3].begin(), moonHistory[3].end(), moons[3]);
      if((searchRes != moonHistory[3].end()) && (iterToRepeat[3] == 0)) {
        cout << "Moon 4 found after " << moonHistory[3].size() << " iterations." << endl;
        iterToRepeat[3] = std::distance(searchRes, moonHistory[3].end());
      }
      else {
        moonHistory[3].push_back(moons[3]);
      }
    }

    return 0;
  }

};

uint16_t

int main() {
  MoonSystem system("input_day12.dat");
  MoonSystem system2("input_day12.dat");

  cout << "Part 1: " << system.part1(1000) << endl;
  system2.part2(1000);

  return 0;
}

uint16_t gcd(Coords_t p) {
  if(p.second == 0)
    return p.first;
  else
    return gcd(std::make_pair(p.second, p.first % p.second));
}