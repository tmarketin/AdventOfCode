def loadPassportData(fname):
  res = []
  with open(fname, 'r') as fp:
    passData = {}
    for line in fp:
      if not line.strip():
        res.append(passData)
        passData = {}
        continue
      fields = line.strip().split()
      for field in fields:
        splitField = field.strip().split(':')
        passData[splitField[0]] = splitField[1]
    res.append(passData)
  return res

def checkAllDataPresent(passItem):
  keysList = ['byr', 'iyr', 'eyr', 'hgt', 'hcl', 'ecl', 'pid']
  presenceList = [key in passItem for key in keysList]
  if False in presenceList:
    return False
  return True

def part1(passList):
  count = 0
  for passItem in passList:
    if(checkAllDataPresent(passItem)):
      count = count + 1
  return count

def validatePassportData(passItem):
  count = 0
  hexList = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
  eyeColorList = ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']

  if(int(passItem['byr']) >= 1920 and int(passItem['byr']) <= 2002):
    count = count + 1

  if(int(passItem['iyr']) >= 2010 and int(passItem['iyr']) <= 2020):
    count = count + 1

  if(int(passItem['eyr']) >= 2020 and int(passItem['eyr']) <= 2030):
    count = count + 1

  if(passItem['hgt'][-2:] == 'cm'):
    hgt = int(passItem['hgt'][:len(passItem['hgt']) - 2])
    if(hgt >= 150 and hgt <= 193):
      count = count + 1
  elif(passItem['hgt'][-2:] == 'in'):
    hgt = int(passItem['hgt'][:len(passItem['hgt']) - 2])
    if(hgt >= 59 and hgt <= 76):
      count = count + 1

  if(passItem['hcl'][0] == '#' and len(passItem['hcl'][1:]) == 6):
    if False in [c in hexList for c in passItem['hcl'][1:]]:
      pass
    else:
      count = count + 1
  
  if(passItem['ecl'] in eyeColorList):
    count = count + 1
  
  if(len(passItem['pid']) == 9 and passItem['pid'].isnumeric()):
    count = count + 1
  
  return count == 7

def part2(passList):
  count = 0
  for passItem in passList:
    if(checkAllDataPresent(passItem) and validatePassportData(passItem)):
      count = count + 1
  return count

input = loadPassportData("input_day4.dat")

print("Solution to part 1: {}".format(part1(input)))
print("Solution to part 2: {}".format(part2(input)))