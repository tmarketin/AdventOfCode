import re

def loadInput(fname):
  res = []
  with open(fname, 'r') as fp:
    for line in fp:
      rowString = re.sub('B', '1', re.sub('F', '0', line.strip()[:7]))
      colString = re.sub('L', '0', re.sub('R', '1', line.strip()[7:]))
      res.append({'row': int(rowString, 2), 'col': int(colString, 2), 'seatID': 8*int(rowString, 2) + int(colString, 2)})
  return res

def part1(input):
  maxSeatId = 0
  for item in input:
    if(item['seatID'] > maxSeatId):
      maxSeatId = item['seatID']
  return maxSeatId

def part2(input):
  occupiedSeats = sorted([item['seatID'] for item in input])
  for idx in range(len(occupiedSeats) - 1):
    if(occupiedSeats[idx + 1] == occupiedSeats[idx] + 2):
      return occupiedSeats[idx] + 1


input = loadInput("input_day5.dat")

print("Solution for part 1: {}".format(part1(input)))
print("Solution for part 2: {}".format(part2(input)))