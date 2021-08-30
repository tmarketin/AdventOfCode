#include <algorithm>
#include <cmath>
#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

typedef std::vector<std::string> AstMap_t;
typedef int16_t Coord_t;
typedef std::pair<Coord_t, Coord_t> Coords_t;
typedef std::set<Coords_t> CoordsSet_t;
typedef std::vector<Coords_t> AstList_t;
typedef std::map<Coords_t, CoordsSet_t> VisibleAstList_t;

void reduceCoords(Coords_t & p);
uint16_t gcd(Coords_t p);

class AsteroidMap {
public:
  AstMap_t astMap;
  AstList_t allAstList;
  VisibleAstList_t visibleList;

  size_t mapWidth;
  size_t mapHeight;

  AsteroidMap(std::string fname) {
    astMap.clear();
    std::ifstream infile(fname);

    std::string line;
    mapHeight = 0;
    while(std::getline(infile, line)) {
      astMap.push_back(line);

      size_t pos = line.find('#', 0);
      while(pos != std::string::npos) {
        allAstList.push_back(std::make_pair(pos, mapHeight));
        pos = line.find('#', pos + 1);
      }
      
      mapHeight++;
    }
    mapWidth = astMap[0].size();

    findVisibleAll();

    return;
  }

  void findVisibleAll() {
    for(auto ast: allAstList) {
      visibleList[ast] = std::set<Coords_t>();
      for(auto astVis: allAstList) {
        if(astVis != ast) {
          Coords_t tmp = std::make_pair(astVis.first - ast.first, astVis.second - ast.second);
          reduceCoords(tmp);
          visibleList[ast].insert(tmp);
        }
      }
    }

    return;
  }

  void printMap() {
    cout << mapWidth << " x " << mapHeight << endl;
    for(auto k: astMap)
      cout << k << endl;
  }

  void printAllAsteroids() {
    for(auto k: allAstList) 
      cout << k.first << ", " << k.second << endl;
    
    return;
  }

  void printVisible() {
    for(auto k: visibleList) {
      cout << k.first.first << ", " << k.first.second << " : " << k.second.size() << endl;
    }
  }

  double getAngle(Coords_t ast, Coords_t origin) {
    Coords_t relCoords = std::make_pair(ast.first - origin.first, -(ast.second - origin.second));

    double angle = std::atan2(relCoords.first, relCoords.second);
    if(angle < 0)
      angle += 2*3.1415926535;

    return angle;
  }

  int32_t killAllAsteroids() {
    Coords_t originAst = findMaxVisible();

    std::map<double, std::deque<std::pair<Coords_t, size_t>>> relAstList;
    for(auto ast: allAstList) {
      if(ast != originAst) {
        double angle = getAngle(ast, originAst);
        relAstList[angle].push_back(std::make_pair(ast, abs(ast.first - originAst.first) + abs(ast.second - originAst.second)));
      }
    }

    for(auto & k: relAstList) {
      std::sort(k.second.begin(), k.second.end(), [](std::pair<Coords_t, size_t> a, std::pair<Coords_t, size_t> b) {
        return a.second < b.second;
      });
    }

    std::vector<Coords_t> killedAst;
    while(! relAstList.empty()) {
      for(auto & k: relAstList) {
        killedAst.push_back(k.second.front().first);
        k.second.pop_front();
      }

      auto iter = relAstList.begin();
      while(iter != relAstList.end()) {
        if(iter->second.empty())
          iter = relAstList.erase(iter);
        else
        iter++;
      }
    }

    return killedAst[199].first*100 + killedAst[199].second;
  }

  size_t part1() {
    return visibleList[findMaxVisible()].size();
  }

  Coords_t findMaxVisible() {
    size_t max = 0;
    Coords_t maxVisAst = std::make_pair(0, 0);
    for(auto k: visibleList) {
      if(k.second.size() > max) {
        max = k.second.size();
        maxVisAst = k.first;
      }
    }

  return maxVisAst;
  }
};

int main() {
  AsteroidMap astMap("input_day10.dat");

  cout << "Part 1: " << astMap.part1() << endl;
  cout << "Part 2: " << astMap.killAllAsteroids() << endl;

  return 0;
}

void reduceCoords(Coords_t & p) {
  Coord_t gFac = gcd(std::make_pair(abs(p.first), abs(p.second)));

  p.first = p.first/gFac;
  p.second = p.second/gFac;

  return;
}

uint16_t gcd(Coords_t p) {
  if(p.second == 0)
    return p.first;
  else
    return gcd(std::make_pair(p.second, p.first % p.second));
}