def loadDataFromFile(fname):
  res = []
  with open(fname, 'r') as fp:
    s = ""
    groupSize = 0
    for line in fp:
      if not line.strip():
        allCountList = [s.count(c) == groupSize for c in set(s)]
        res.append({'str': s, 'set': set(s), 'anyCount': len(set(s)), 'gSize': groupSize, 'allCount': allCountList.count(True)})
        s = ""
        groupSize = 0
        continue
      s = s + line.strip()
      groupSize += 1
    allCountList = [s.count(c) == groupSize for c in set(s)]
    res.append({'str': s, 'set': set(s), 'anyCount': len(set(s)), 'gSize': groupSize, 'allCount': allCountList.count(True)})
  return res

def part1(groups):
  res = 0
  for group in groups:
    res = res + group['anyCount']
  return res

def part2(groups):
  res = 0
  for group in groups:
    res = res + group['allCount']
  return res


inputGroups = loadDataFromFile("input_day6.dat")

print("Solution to part 1: {}".format(part1(inputGroups)))
print("Solution to part 2: {}".format(part2(inputGroups)))