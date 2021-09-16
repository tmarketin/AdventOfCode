from bitmaskCode import BitmaskCode

import re

def loadFromFile(fname):
  res = []
  with open(fname, 'r') as fp:
    for line in fp:
      tmpLine = [item.strip() for item in line.strip().split('=')]
      if tmpLine[0] == 'mask':
        res.append(tmpLine)
      else:
        tmpStr = re.sub('[\[\]]', ' ', tmpLine[0]).strip().split()
        res.append([tmpStr[0], int(tmpStr[1]), int(tmpLine[1])])
  return res

def part1(input):
  executor = BitmaskCode(input)
  executor.executeCode()
  return executor.getMemorySum()

input = loadFromFile("input_day14.dat")

print("Solution to part 1: {}".format(part1(input)))