from ship import Ship

def loadFromFile(fname):
  res = []
  with open(fname, 'r') as fp:
    for line in fp:
      stripLine = line.strip()
      res.append({'command': stripLine[0], 'value': int(stripLine[1:])})
  return res

def part1(ship):
  ship.executeInstructions()
  return ship.getCurrentDistance()

def part2(ship):
  ship.resetShip()
  ship.executeInstructionsToWaypoint()
  return ship.getCurrentDistance()

input = loadFromFile("input_day12.dat")
ship = Ship(input)

print("Solution to part 1: {}".format(part1(ship)))
print("Solution to part 2: {}".format(part2(ship)))