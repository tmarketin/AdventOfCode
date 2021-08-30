#ifndef INTCODE_H
#define INTCODE_H

#include <array>
#include <deque>
#include <fstream>
#include <functional>
#include <map>
#include <sstream>
#include <string>

typedef int32_t Key_t;
typedef int64_t Value_t;
typedef uint16_t ExitSignal_t;
typedef std::deque<Value_t> Buffer_t;
typedef std::map<Key_t, Value_t> Program_t;

class Intcode {
public:
  const std::array<int32_t, 10> op_len = {{-1, 3, 3, 1, 1, 2, 2, 3, 3, 1}};
  Key_t instrPtr;
  Key_t relBase;

  Program_t code;
  std::map<int32_t, std::function<void(Intcode *, Key_t, Key_t, Key_t, ExitSignal_t &)>> ops;
  std::string initialCode;

  Buffer_t inputBuffer;
  Buffer_t outputBuffer;

  void setupOperations();
  void handleOperands(const Key_t instrPtr, Key_t & op1, Key_t & op2, Key_t & op3);
  Key_t handleSingleOperand(const Key_t instrPtr, int32_t paramType);

  Intcode(std::string fname);

  void printCode();
  void printBuffers();

  void resetCode();
  void setCode(Key_t key, Value_t value);
  Value_t getValue(Key_t key);

  void addToInput(Value_t val);
  Value_t readFromInput();
  Value_t getOutput();
  bool areBuffersEmpty();

  void executeProgram();
  bool isExecutionFinished();
};

typedef std::map<int32_t, std::function<void(Intcode *, Key_t, Key_t, Key_t, ExitSignal_t &)>> Operations_t;

#endif