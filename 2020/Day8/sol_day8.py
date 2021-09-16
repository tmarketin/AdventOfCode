import sys
sys.path.append('../Utils')

from bootcode import BootCode

def loadFromFile(fname):
  res = []
  with open(fname, 'r') as fp:
    for line in fp:
      splitLine = line.strip().split()
      res.append({'op': splitLine[0], 'arg': int(splitLine[1])})
  return res

def part1(input):
  bc = BootCode(input)
  code, value = bc.runProgram()
  return value

def part2(input):
  instIdx = 0
  retCode = 1
  programLength = len(input)
  while instIdx < programLength and retCode == 1:
    if input[instIdx]['op'] == 'acc':
      instIdx = instIdx + 1
      continue

    if input[instIdx]['op'] == 'jmp':
      input[instIdx]['op'] = 'nop'
      bc = BootCode(input)
      retCode, value = bc.runProgram()
      input[instIdx]['op'] = 'jmp'
    else:
      input[instIdx]['op'] = 'jmp'
      bc = BootCode(input)
      retCode, value = bc.runProgram()
      input[instIdx]['op'] = 'nop'
    if retCode == 0:
      print("Changed instruction {}".format(instIdx))
      break
    instIdx = instIdx + 1
  return value

input = loadFromFile("input_day8.dat")

print("Solution to part 1: {}".format(part1(input)))
print("Solution to part 2: {}".format(part2(input)))