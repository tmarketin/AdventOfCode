#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "../Libs/intcode.h"

using std::cout;
using std::endl;

typedef std::vector<Intcode> AmplifierArray_t;

int32_t getTotalPhase(const std::vector<Value_t> & phase);

void fillAmpArray(AmplifierArray_t & ampArray, std::vector<Value_t> & phase);
Value_t executeAmpArray(AmplifierArray_t & ampArray);
Value_t executeAmpArrayWithFeedback(AmplifierArray_t & ampArray);
void resetAmpArray(AmplifierArray_t & ampArray);

int32_t part1(AmplifierArray_t & ampArray);
int32_t part2(AmplifierArray_t & ampArray);

int main() {
  AmplifierArray_t ampArray;
  for(size_t idx = 0; idx < 5; idx++)
    ampArray.push_back(Intcode("input_day7.dat"));

  cout << "Part 1: " << part1(ampArray) << endl;
  cout << "Part 2: " << part2(ampArray) << endl;

  return 0;
}

int32_t part1(AmplifierArray_t & ampArray) {
  std::vector<Value_t> phase = {{0, 1, 2, 3, 4}};
  std::pair<int32_t, int32_t> maxRes = std::make_pair(0, 0);

  do {
    fillAmpArray(ampArray, phase);
    Value_t res = executeAmpArray(ampArray);
    if(res > maxRes.second) {
      maxRes.first = getTotalPhase(phase);
      maxRes.second = res;
    }
    resetAmpArray(ampArray);
  } while(std::next_permutation(phase.begin(), phase.end()));

  return maxRes.second;
}

int32_t part2(AmplifierArray_t & ampArray) {
  std::vector<Value_t> phase = {{5, 6, 7, 8, 9}};
  std::pair<int32_t, int32_t> maxRes = std::make_pair(0, 0);

  do {
    fillAmpArray(ampArray, phase);
    Value_t res = executeAmpArrayWithFeedback(ampArray);
    if(res > maxRes.second) {
      maxRes.first = getTotalPhase(phase);
      maxRes.second = res;
    }
    resetAmpArray(ampArray);
  } while(std::next_permutation(phase.begin(), phase.end()));

  return maxRes.second;
}

int32_t getTotalPhase(const std::vector<Value_t> & phase) {
  int32_t res = 0;

  for(auto k: phase)
    res = res*10 +k;

  return res;
}

void fillAmpArray(AmplifierArray_t & ampArray, std::vector<Value_t> & phase) {
  for(size_t idx = 0; idx < 5; idx++)
    ampArray[idx].addToInput(phase[idx]);

  return;
}

Value_t executeAmpArray(AmplifierArray_t & ampArray) {
  ampArray[0].addToInput(0);

  for(size_t idx = 0; idx < 4; idx++) {
    ampArray[idx].executeProgram();
    ampArray[idx + 1].addToInput(ampArray[idx].getOutput());
  }
  ampArray[4].executeProgram();

  return ampArray[4].getOutput();
}

Value_t executeAmpArrayWithFeedback(AmplifierArray_t & ampArray) {
  Value_t tmpVal = 0;

  do {
    ampArray[0].addToInput(tmpVal);
    for(size_t idx = 0; idx < 4; idx++) {
      ampArray[idx].executeProgram();
      ampArray[idx + 1].addToInput(ampArray[idx].getOutput());
    }
    ampArray[4].executeProgram();
    tmpVal = ampArray[4].getOutput();
  } while(! ampArray[4].isExecutionFinished());

  return tmpVal;
}

void resetAmpArray(AmplifierArray_t & ampArray) {
  for(size_t idx = 0; idx < 5; idx++)
    ampArray[idx].resetCode();
  
  return;
}
