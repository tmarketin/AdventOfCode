class BootCode:
  def __init__(self, program):
    self.program = program
    self.acc = 0
    self.execIdx = 0
    self.execList = []

    self.opMapper = {'acc': self.execAcc,
                     'jmp': self.execJmp,
                     'nop': self.execNoOp}

  def resetProgram(self):
    self.acc = 0
    self.execIdx = 0
    self.execList = []

  def execAcc(self, arg):
    self.acc = self.acc + arg
    self.execIdx = self.execIdx + 1
  
  def execJmp(self, arg):
    self.execIdx = self.execIdx + arg
  
  def execNoOp(self, arg):
    self.execIdx = self.execIdx + 1

  def runProgram(self):
    """ return code 0 if program exited successfully,
    return code 1 if exited by repeating instruction """
    self.resetProgram()
    programLength = len(self.program)
    while self.execIdx not in self.execList and self.execIdx < programLength:
      self.execList.append(self.execIdx)
      op = self.program[self.execIdx]['op']
      arg = self.program[self.execIdx]['arg']
      self.opMapper[op](arg)
    if self.execIdx >= programLength:
      return 0, self.acc
    else:
      return 1, self.acc

  def printProgram(self):
    for line in self.program:
      print(line)
