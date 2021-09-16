import math

def loadFromFile(fname):
  res = {}
  with open(fname, 'r') as fp:
    content = [line.strip() for line in fp]
  res['startTime'] = int(content[0])
  res['lines'] = content[1].strip().split(',')
  return res

def part1(input):
  res = []
  for line in input['lines']:
    if line != 'x':
      lineId = int(line)
      res.append({'lineId': lineId, 'timeDiff': lineId*(math.floor(input['startTime']/lineId) + 1) - input['startTime']})
  waitingTimeList = [item['timeDiff'] for item in res]
  minWaitingTime = min(waitingTimeList)
  pos = waitingTimeList.index(minWaitingTime)
  return res[pos]['lineId']*minWaitingTime

def checkDivisibility(num, linesList):
  resList = [(item['id'] - (num % item['id'])) % item['id'] == item['pos'] for item in linesList]
  print(num, resList)
  if False in resList:
    return False
  return True

def findNextValue(counter, step, item):
  print(counter, step, item['id'], item['pos'])
  while True:
    counter = counter + step
    if counter % item['id'] == item['id'] - (item['pos'] % item['id']):
      return counter

def part2(input):
  linesList = []
  for idx in range(len(input['lines'])):
    if input['lines'][idx] != 'x':
      lineId = int(input['lines'][idx])
      linePos = idx
      linesList.append({'id': lineId, 'pos': linePos})
#  linesList.sort(key=lambda item: item['id'])

  counterStep = linesList[0]['id']
  counter = 0
  for item in linesList[1:]:
    counter = findNextValue(counter, counterStep, item)
    counterStep = counterStep*item['id']
  return counter

input = loadFromFile("input_day13.dat")

print("Solution to part 1: {}".format(part1(input)))
print("Solution to part 2: {}".format(part2(input)))