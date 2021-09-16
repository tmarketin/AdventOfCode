class BitmaskCode:
  def __init__(self, instructions):
    self.mask = ''
    self.mem = {}
    self.instructions = instructions

  def applyMask(self, value):
    bitValue = '{0:0{1}b}'.format(value, 36)
    bitValueList = list(bitValue)
    maskList = list(self.mask)
    for idx in range(len(maskList)):
      if maskList[idx] != 'X':
        bitValueList[idx] = maskList[idx]
    return int(''.join(bitValueList), 2)

  def executeCode(self):
    for line in self.instructions:
      if line[0] == 'mask':
        self.mask = line[1]
      else:
        pos = line[1]
        value = line[2]
        self.mem[pos] = self.applyMask(value)
  
  def getMemorySum(self):
    count = 0
    for key, value in self.mem.items():
      count = count + value
    return count

  def printMemory(self):
    print(self.mem)
  

