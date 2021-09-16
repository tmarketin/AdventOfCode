def loadFromFile(fname):
  res = []
  with open(fname, 'r') as fp:
    for line in fp:
      res.append(int(line.strip()))
  return res

def isSumOfTwo(num, numList):
  sortedList = sorted(numList)
  listLength = len(sortedList)
  for idxOuter in range(listLength - 1):
    for idxInner in range(idxOuter + 1, listLength):
      sumTwo = sortedList[idxInner] + sortedList[idxOuter]
      if sumTwo == num:
#        print("{} = {} + {}".format(num, sortedList[idxOuter], sortedList[idxInner]))
        return True
      if sumTwo > num:
        break
  return False

def part1(input, numBack):
  idx = numBack
  while idx < len(input):
    if not isSumOfTwo(input[idx], input[idx - numBack: idx]):
      return input[idx]
    idx = idx + 1

def part2(input, numBack):
  fixNum = part1(input, numBack)
  for idxBegin in range(len(input)):
    for idxEnd in range(idxBegin, len(input)):
      tmpSum = sum(input[idxBegin:idxEnd])
      if tmpSum == fixNum:
        resList = sorted(input[idxBegin:idxEnd])
        return resList[0] + resList[-1]
      if tmpSum > fixNum:
        break
  return 0

input = loadFromFile("input_day9.dat")

print("Solution to part 1: {}".format(part1(input, 25)))
print("Solution to part 2: {}".format(part2(input, 25)))