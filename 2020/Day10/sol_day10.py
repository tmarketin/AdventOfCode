def loadFromFile(fname):
  res = []
  with open(fname, 'r') as fp:
    for line in fp:
      res.append(int(line.strip()))
  return res

def part1(input):
  adapterList = sorted(input)
  usedList = []
  diffCount = [0, 0, 0, 0]
  currRating = 0
  while adapterList:
    lowAdapter = adapterList.pop(0)
    ratingDiff = lowAdapter - currRating
    if ratingDiff <= 3:
      diffCount[ratingDiff] += 1
      usedList.append(lowAdapter)
      currRating = lowAdapter
  diffCount[3] += 1
  currRating += 3
  return diffCount[1]*diffCount[3]

def getCombinations(usedList, adapterList):
  ratingDiff = adapterList[0] - usedList[-1]
  if ratingDiff > 3:
    return 0
  else:
    if len(adapterList) == 1:
      return 1
    countWith = getCombinations(usedList + [adapterList[0]], adapterList[1:])
    countWithout = 0
    if adapterList[1] - usedList[-1] <= 3:
      countWithout = getCombinations(usedList, adapterList[1:])
    return countWith + countWithout

def generateSublists(adapterList):
  res = []
  sublist = []
  for idx in range(1, len(adapterList)):
    currRating = adapterList[idx - 1]
    diffFirst = adapterList[idx] - currRating
    if diffFirst == 3:
      if sublist:
        sublist.append(currRating)
        res.append(sublist)
        sublist = []
      continue
    else:
      sublist.append(currRating)
  if sublist:
    res.append(sublist)
  return res

def part2(input):
  adapterList = [0] + sorted(input)
  deviceRating = adapterList[-1] + 3
  adapterList.append(deviceRating)
  sublists = generateSublists(adapterList)

  product = 1
  for item in sublists:
    comb = getCombinations([item[0]], item[1:])
    print(item, comb)
    product = product*comb
  return product

def getCombinationsWithMemo(usedList, adapterList, savedCalls):
  ratingDiff = adapterList[0] - usedList[-1]
  if ratingDiff > 3:
    return 0
  else:
    if len(adapterList) == 1:
      return 1
    argsWith = (adapterList[0], tuple(adapterList[1:]))
    if argsWith in savedCalls:
      countWith = savedCalls[argsWith]
    else:
      countWith = getCombinationsWithMemo(usedList + [adapterList[0]], adapterList[1:], savedCalls)
      savedCalls[argsWith] = countWith
    countWithout = 0
    if adapterList[1] - usedList[-1] <= 3:
      argsWithout = (usedList[-1], tuple(adapterList[1:]))
      if argsWithout in savedCalls:
        countWithout = savedCalls[argsWithout]
      else:
        countWithout = getCombinationsWithMemo(usedList, adapterList[1:], savedCalls)
        savedCalls[argsWithout] = countWithout
    return countWith + countWithout

def part2Recursive(input):
  adapterList = [0] + sorted(input) + [max(input) + 3]
  savedCalls = {}
  count = getCombinationsWithMemo([adapterList[0]], adapterList[1:], savedCalls)

  return count

input = loadFromFile("input_day10.dat")

print("Solution to part 1: {}".format(part1(input)))
print("Solution to part 2: {}".format(part2(input)))

print("Recursive solution: {}".format(part2Recursive(input)))