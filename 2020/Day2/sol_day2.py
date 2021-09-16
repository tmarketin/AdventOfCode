import re

def loadDataFromFile(fname):
  res = []
  with open(fname, "r") as fp:
    for line in fp:
      newLine = re.sub('[-:]', ' ', line)
      splitLine = newLine.strip().split()
      passItem = {'min': int(splitLine[0]), 'max': int(splitLine[1]), 'character': splitLine[2], 'password': splitLine[3]}
      res.append(passItem)
  return res

def part1(input):
  res = 0
  for passItem in input:
    count = passItem['password'].count(passItem['character'])
    if(count >= passItem['min'] and count <= passItem['max']):
      res = res + 1
  return res

def part2(input):
  res = 0
  for passItem in input:
    count = 0
    if(passItem['password'][passItem['min'] - 1] == passItem['character']):
      count = count + 1
    if(passItem['password'][passItem['max'] - 1] == passItem['character']):
      count = count + 1
    if(count == 1):
      res = res + 1
  return res
    

input = loadDataFromFile("input_day2.dat")

print("Solution to part 1: {}".format(part1(input)))
print("Solution to part 2: {}".format(part2(input)))