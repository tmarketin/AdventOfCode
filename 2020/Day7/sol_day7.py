import re

def loadDataFromFile(fname):
  res = []
  with open(fname, 'r') as fp:
    for line in fp:
      lineStep = re.sub('bags contain|bag\,|bags\,', ':', line.strip())
      lineClean = re.sub('bag\.|bags\.', '', lineStep)
      lineSplit = lineClean.strip().split(':')
      containerColor = lineSplit[0].strip()
      subItems = []
      for item in lineSplit[1:]:
        strippedItem = item.strip()
        if strippedItem == "no other":
          continue
        contentSize = int(strippedItem[0])
        contentColor = strippedItem[1:].strip()
        subItems.append({'size': contentSize, 'color': contentColor})
      res.append({'container': containerColor, 'content': subItems})
  return res

def part1(bagMap):
  initialColor = 'shiny gold'
  workList = [item['container'] for item in bagMap if initialColor in [bag['color'] for bag in item['content']]]
  res = workList.copy();
  while workList:
    workItem = workList.pop(0)
    containers = [item['container'] for item in bagMap if workItem in [bag['color'] for bag in item['content']]]
    for item in containers:
      if item not in res:
        res.append(item)
        if item not in workList:
          workList.append(item)
  return len(res)

def getBagContent(bagMap, color):
  for item in bagMap:
    if item['container'] == color:
      return item['content']

def part2(bagMap, initialColor):
  bagCount = 0
  workList = getBagContent(bagMap, initialColor)
  if workList:
    for item in workList:
      bagCount = bagCount + item['size']*(part2(bagMap, item['color']) + 1)
  else:
    bagCount = 0
  return bagCount

bagMapping = loadDataFromFile("input_day7.dat")

print("Solution for part 1: {}".format(part1(bagMapping)))
print("Solution for part 2: {}".format(part2(bagMapping, 'shiny gold')))