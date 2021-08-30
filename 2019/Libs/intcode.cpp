#include <iostream>

#include "intcode.h"

using std::cout;
using std::cin;
using std::endl;

Intcode::Intcode(std::string fname) {
  std::fstream infile(fname);

  instrPtr = 0;
  relBase = 0;

  std::getline(infile, initialCode);
  resetCode();
  setupOperations();

  return;
}

void Intcode::addToInput(Value_t val) {
  inputBuffer.push_back(val);

  return;
}

Value_t Intcode::readFromInput() {
  Value_t num = inputBuffer.front();
  inputBuffer.pop_front();

  return num;
}

Value_t Intcode::getOutput() {
  Value_t num = outputBuffer.front();
  outputBuffer.pop_front();

  return num;
}


void Intcode::setupOperations() {
  ops[1] = [](Intcode * prog, Key_t op1, Key_t op2, Key_t op3, ExitSignal_t & killThread) {
    prog->code[op3] = prog->code[op1] + prog->code[op2];

    prog->instrPtr += 4;

    return;
  };

  ops[2] = [](Intcode * prog, Key_t op1, Key_t op2, Key_t op3, ExitSignal_t & killThread) {
    prog->code[op3] = (prog->code[op1])*(prog->code[op2]);

    prog->instrPtr += 4;

    return;
  };

  ops[3] = [](Intcode * prog, Key_t op1, Key_t op2, Key_t op3, ExitSignal_t & killThread) {
    if(! prog->inputBuffer.empty()) {
      prog->code[op1] = prog->inputBuffer.front();
      prog->inputBuffer.pop_front();
      
      prog->instrPtr += 2;
    }
    else {
      killThread = 1;
    }

    return;
  };

  ops[4] = [](Intcode * prog, Key_t op1, Key_t op2, Key_t op3, ExitSignal_t & killThread) {
    prog->outputBuffer.push_back(prog->code[op1]);
    prog->instrPtr += 2;

    return;
  };

  ops[5] = [](Intcode * prog, Key_t op1, Key_t op2, Key_t op3, ExitSignal_t & killThread) {
    if(prog->code[op1] != 0)
      prog->instrPtr = prog->code[op2];
    else
      prog->instrPtr += 3;

    return;
  };

  ops[6] = [](Intcode * prog, Key_t op1, Key_t op2, Key_t op3, ExitSignal_t & killThread) {
    if(prog->code[op1] == 0)
      prog->instrPtr = prog->code[op2];
    else
      prog->instrPtr += 3;

    return;
  };

  ops[7] = [](Intcode * prog, Key_t op1, Key_t op2, Key_t op3, ExitSignal_t & killThread) {
    prog->code[op3] = prog->code[op1] < prog->code[op2] ? 1 : 0;

    prog->instrPtr += 4;

    return;
  };

  ops[8] = [](Intcode * prog, Key_t op1, Key_t op2, Key_t op3, ExitSignal_t & killThread) {
    prog->code[op3] = prog->code[op1] == prog->code[op2] ? 1 : 0;

    prog->instrPtr += 4;

    return;
  };

  ops[9] = [](Intcode * prog, Key_t op1, Key_t op2, Key_t op3, ExitSignal_t & killThread) {
    prog->relBase += prog->code[op1];

    prog->instrPtr += 2;

    return;
  };

  return;
}

void Intcode::executeProgram() {
  ExitSignal_t killThread = 0;

  Key_t op1 = 0;
  Key_t op2 = 0;
  Key_t op3 = 0;

  while(code[instrPtr] != 99 && killThread == 0) {
    int32_t opmask = code[instrPtr]/100;
    int32_t opval = code[instrPtr] % 100;
    handleOperands(instrPtr, op1, op2, op3);
    ops[opval](this, op1, op2, op3, killThread);
  }

  return;
}

void Intcode::handleOperands(const Key_t instrPtr, Key_t & op1, Key_t & op2, Key_t & op3) {
  int32_t opmask = code[instrPtr]/100;
  int32_t opvalue = code[instrPtr] % 100;

  int32_t pType1 = opmask % 10;
  int32_t pType2 = (opmask/10) % 10;
  int32_t pType3 = opmask/100;

  op1 = handleSingleOperand(instrPtr + 1, pType1);
  if(op_len[opvalue] >= 2)
    op2 = handleSingleOperand(instrPtr + 2, pType2);
  if(op_len[opvalue] >= 3)
    op3 = handleSingleOperand(instrPtr + 3, pType3);

  return;
}

Key_t Intcode::handleSingleOperand(const Key_t instrPtr, int32_t paramType) {
  if(paramType == 0)
    return code[instrPtr];
  else if(paramType == 1)
    return instrPtr;
  else if(paramType == 2)
    return code[instrPtr] + this->relBase;
}

void Intcode::resetCode() {
  std::stringstream iss(initialCode);

  std::string shortline;
  int32_t idx = 0;
  while(std::getline(iss, shortline, ',')) {
    code[idx++] = std::stoll(shortline);
  }
  instrPtr = 0;
  relBase = 0;

  inputBuffer.clear();
  outputBuffer.clear();

  return;
}

void Intcode::printCode() {
  for(auto k: code)
    cout << k.first << " " << k.second << endl;
  
  return;
}

void Intcode::setCode(Key_t key, Value_t value) {
  code[key] = value;

  return;
}

Value_t Intcode::getValue(Key_t key) {
  return code[key];
}

bool Intcode::areBuffersEmpty() {
  return inputBuffer.empty() || outputBuffer.empty();
}

void Intcode::printBuffers() {
  if(inputBuffer.empty()) {
    cout << "Input buffer is empty." << endl;
  }
  else {
    cout << "Input buffer: ";
    while(! inputBuffer.empty()) {
      cout << inputBuffer.front() << " ";
      inputBuffer.pop_front();
    }
    cout << endl;
  }

  if(outputBuffer.empty()) {
    cout << "Output buffer is empty." << endl;
  }
  else {
    cout << "Output buffer: ";
    while(! outputBuffer.empty()) {
      cout << outputBuffer.front() << " ";
      outputBuffer.pop_front();
    }
    cout << endl;
  }

  return;
}

bool Intcode::isExecutionFinished() {
  return code[instrPtr] == 99;
}