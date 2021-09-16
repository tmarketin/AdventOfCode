def loadMap(fname):
  res = []
  with open(fname, 'r') as fp:
    for line in fp:
      res.append(line.strip().split()[0])
  return res

def part1(map, step):
  pos = {'x': 0, 'y': 0}
  mapWidth = len(map[0])
  treeCount = 0
  while(pos['y'] < len(map) - 1):
    pos['x'] = (pos['x'] + step['x']) % mapWidth
    pos['y'] += step['y']
    if(map[pos['y']][pos['x']] == '#'):
      treeCount += 1
  return treeCount

def part2(map):
  steps = [{'x': 1, 'y': 1}, {'x': 3, 'y': 1}, {'x': 5, 'y': 1}, {'x': 7, 'y': 1}, {'x': 1, 'y': 2}]
  treeCounts = [part1(map, step) for step in steps]
  product = 1;
  for count in treeCounts:
    product = product*count
  return product

map = loadMap("input_day3.dat")

print("Part1 solution: {}".format(part1(map, {'x': 3, 'y': 1})))
print("Part2 solution: {}".format(part2(map)))