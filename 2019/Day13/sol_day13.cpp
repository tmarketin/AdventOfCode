#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <set>
#include <utility>

#include "../Libs/intcode.h"

using std::cin;
using std::cout;
using std::endl;

typedef std::pair<int32_t, int32_t> Coords_t;
typedef std::map<Coords_t, int32_t> Gamestate_t;

class Game {
public:
  Intcode * program;

  Gamestate_t gameState;

  Game(std::string fname) {
    program = new Intcode(fname);
  }

  void convertOutputToGameState() {
    gameState.clear();

    auto iter = program->outputBuffer.begin();
    while(iter != program->outputBuffer.end()) {
      gameState.emplace(std::make_pair(std::make_pair(*iter, *(iter + 1)), *(iter + 2)));
      iter += 3;
    }
    return;
  }

  void printGameState() {
    for(auto k: gameState)
      cout << k.first.first << ", " << k.first.second << " : " << k.second << endl;
  }

  void drawGameState() {
    for(int32_t y = 0; y <= 21; y++) {
      for(int32_t x = 0; x <= 42; x++) {
        switch(gameState[std::make_pair(x, y)]) {
          case 0:
            cout << " ";
            break;
          case 1: // wall
            cout << "#";
            break;
          case 2: // block
            cout << "=";
            break;
          case 3: // paddle
            cout << "_";
            break;
          case 4: // ball
            cout << "*";
            break;
        }
      }
      cout << endl;
    }
  }

  int32_t part1() {
    int32_t cnt = 0;
    for(auto k: gameState)
      if(k.second == 2)
        cnt++;
    
    return cnt;
  }

  void part2() {
    int32_t turnCnt = 0;
    int32_t inputVal;
    Coords_t scoreCoord = std::make_pair(-1, 0);
    while(part1() > 0) {
      cout << "Turn " << turnCnt++ << endl;
      program->executeProgram();
      convertOutputToGameState();
      drawGameState();
      if(! program->isExecutionFinished()) {
        cout << "Execution ongoing" << endl;
        cout << "Current score: " << gameState[scoreCoord] << endl;
        cout << "Input input: ";
        cin >> inputVal;
        program->addToInput(inputVal);
      }
    }

    return;
  }

};

int main() {
  Game game("input_day13.dat");

  game.program->executeProgram();
  game.convertOutputToGameState();
  cout << "Part 1: " << game.part1() << endl;
  
  game.program->resetCode();
  game.program->setCode(0, 2);
  game.part2();

  return 0;
}