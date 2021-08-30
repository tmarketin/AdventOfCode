def loadFromFile(fname):
    with open(fname, 'r') as fp:
        for line in fp:
            return [int(k) for k in line.strip().split(',')]

def initMapping(mapping, input):
    for idx in range(len(input) - 1):
        mapping[input[idx]] = idx + 1

def playGame(input, maxTurn):
    mapping = {}
    initMapping(mapping, input)

    turn = len(input)
    currentNumber = input[-1]
    while turn <= maxTurn:
        if currentNumber in mapping:
            nextNumber = turn - mapping[currentNumber]
        else:
            nextNumber = 0
        mapping[currentNumber] = turn
        turn = turn + 1
        currentNumber = nextNumber
    return currentNumber

def part1(input):
    return playGame(input, 2019)

def part2(input):
    return playGame(input, 29999999)

input = loadFromFile("input_day15.dat")

print("Solution to part 1: {}".format(part1(input)))
print("Solution to part 2: {}".format(part2(input)))