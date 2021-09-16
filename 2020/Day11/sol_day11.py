import copy

def loadMapFromFile(fname):
  res = []
  with open(fname, 'r') as fp:
    for line in fp:
      res.append(list(line.strip()))
  return res

def mapPrint(seats):
  for line in seats:
    print(''.join(line))

def countAdjacent(y, x, seats):
  mapSize = len(seats)
  lineSize = len(seats[0])
  surrSeats = []
  if y > 0:
    if x > 0:
      surrSeats.append(seats[y - 1][x - 1])
    if x < (lineSize - 1):
      surrSeats.append(seats[y - 1][x + 1])
    surrSeats.append(seats[y - 1][x])
  if y < (mapSize - 1):
    if x > 0:
      surrSeats.append(seats[y + 1][x - 1])
    if x < (lineSize - 1):
      surrSeats.append(seats[y + 1][x + 1])
    surrSeats.append(seats[y + 1][x])
  if x > 0:
    surrSeats.append(seats[y][x - 1])
  if x < (lineSize - 1):
    surrSeats.append(seats[y][x + 1])
  
  return surrSeats.count('#')

def countDirections(y, x, seats):
  mapSize = len(seats)
  lineSize = len(seats[0])
  surrSeats = []
  # up
  yIdx = y - 1
  xIdx = x
  while yIdx >= 0:
    if seats[yIdx][xIdx] != '.':
      surrSeats.append(seats[yIdx][xIdx])
      break
    yIdx -= 1
  # up - right
  yIdx = y - 1
  xIdx = x + 1
  while yIdx >= 0 and xIdx <= (lineSize - 1):
    if seats[yIdx][xIdx] != '.':
      surrSeats.append(seats[yIdx][xIdx])
      break
    yIdx -= 1
    xIdx += 1
  # right
  yIdx = y
  xIdx = x + 1
  while xIdx <= (lineSize - 1):
    if seats[yIdx][xIdx] != '.':
      surrSeats.append(seats[yIdx][xIdx])
      break
    xIdx += 1
  # down - right
  yIdx = y + 1
  xIdx = x + 1
  while yIdx <= (mapSize - 1) and xIdx <= (lineSize - 1):
    if seats[yIdx][xIdx] != '.':
      surrSeats.append(seats[yIdx][xIdx])
      break
    yIdx += 1
    xIdx += 1
  # down
  yIdx = y + 1
  xIdx = x
  while yIdx <= (mapSize - 1):
    if seats[yIdx][xIdx] != '.':
      surrSeats.append(seats[yIdx][xIdx])
      break
    yIdx += 1
  # down - left
  yIdx = y + 1
  xIdx = x - 1
  while yIdx <= (mapSize - 1) and xIdx >= 0:
    if seats[yIdx][xIdx] != '.':
      surrSeats.append(seats[yIdx][xIdx])
      break
    yIdx += 1
    xIdx -= 1
  # left
  yIdx = y
  xIdx = x - 1
  while xIdx >= 0:
    if seats[yIdx][xIdx] != '.':
      surrSeats.append(seats[yIdx][xIdx])
      break
    xIdx -= 1
  # up - left
  yIdx = y - 1
  xIdx = x - 1
  while yIdx >= 0 and xIdx >= 0:
    if seats[yIdx][xIdx] != '.':
      surrSeats.append(seats[yIdx][xIdx])
      break
    yIdx -= 1
    xIdx -= 1
  
  return surrSeats.count('#')

def countAllOccupied(seats):
  count = 0
  for line in seats:
    count = count + line.count('#')
  
  return count

def solution(seats, countCall, occupiedLimit):
  mapSize = len(seats)
  lineSize = len(seats[0])
  oldSeats = copy.deepcopy(seats)
  newSeats = copy.deepcopy(seats)
  while True:
    changeFlag = False
    for mapIdx in range(mapSize):
      for lineIdx in range(lineSize):
        if oldSeats[mapIdx][lineIdx] == '.':
          continue
        count = countCall(mapIdx, lineIdx, oldSeats)
#        print(mapIdx, lineIdx, oldSeats[mapIdx][lineIdx], count)
        if oldSeats[mapIdx][lineIdx] == 'L' and count == 0:
          newSeats[mapIdx][lineIdx] = '#'
          changeFlag = True
        elif oldSeats[mapIdx][lineIdx] == '#' and count >= occupiedLimit:
          newSeats[mapIdx][lineIdx] = 'L'
          changeFlag = True
    oldSeats = copy.deepcopy(newSeats)

    if not changeFlag:
      break

  return countAllOccupied(newSeats)

input = loadMapFromFile("input_day11.dat")

print("Solution to part 1: {}".format(solution(copy.deepcopy(input), countAdjacent, 4)))
print("Solution to part 2: {}".format(solution(copy.deepcopy(input), countDirections, 5)))



"""
    If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
    If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
    Otherwise, the seat's state does not change.

At this point, something interesting happens: the chaos stabilizes and further applications of these rules cause no seats to change state! Once people stop moving around, you count 37 occupied seats.

Simulate your seating area by applying the seating rules repeatedly until no seats change state. How many seats end up occupied? """