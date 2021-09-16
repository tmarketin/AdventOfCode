def loadDataFromFile(fname):
  res = []
  with open(fname, "r") as fp:
    for line in fp:
      res.append(int(line.strip()))
  return sorted(res)

def part1(input):
  listSize = len(input)
  for outerIdx in range(listSize - 1):
    for innerIdx in range(outerIdx + 1, listSize):
      inputSum = input[outerIdx] + input[innerIdx]
      if(inputSum == 2020):
        inputProduct = input[outerIdx]*input[innerIdx]
        print("Solution to part 1: {}".format(inputProduct))
        return inputProduct
      elif(inputSum > 2020):
        break
  return 0

def part2(input):
  listSize = len(input)
  for idx1 in range(listSize - 2):
    if(input[idx1] > 2020):
      break
    for idx2 in range(idx1 + 1, listSize - 1):
      twoSum = input[idx1] + input[idx2]
      if(twoSum > 2020 - input[idx2 + 1]):
        break
      for idx3 in range(idx2 + 1, listSize):
        threeSum = twoSum + input[idx3]
        if(threeSum == 2020):
          threeProduct = input[idx1]*input[idx2]*input[idx3]
          print("Solution to part2: {} * {} * {} = {}".format(input[idx1], input[idx2], input[idx3], threeProduct))
          return
        elif(threeSum > 2020):
          break
  return 0

inputFname = "input_day1.dat"
input = loadDataFromFile(inputFname)

part1(input)
part2(input)