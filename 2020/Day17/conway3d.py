from collections import defaultdict
import copy

class Conway:
    system = defaultdict(lambda: '.')
    initSystem = defaultdict(lambda: '.')

    def __init__(self, fname):
        self.loadFromFile(fname)
        self.initSystem = copy.deepcopy(self.system)
    
    def printSystem(self):
        for key, value in self.system.items():
            print(key, value)

    def countActive(self):
        return sum(1 for key, value in self.system.items() if value == '#')

    def countActiveInList(self, coords, sys):
        return sum(1 for item in coords if sys[item] == '#')

    def loadFromFile(self, fname):
        z = 0
        w = 0
        with open(fname, 'r') as fp:
            y = 0
            for line in fp:
                splitLine = list(line.strip())
                for idx in range(len(splitLine)):
                    self.system[(idx, y, z, w)] = splitLine[idx]
                y = y - 1

    def getNeighbourCoords3d(self, sys, key):
        res = []
        w = 0
        for x in range(key[0] - 1, key[0] + 2):
            for y in range(key[1] - 1, key[1] + 2):
                for z in range(key[2] - 1, key[2] + 2):
                    res.append((x, y, z, w))
        res.remove(key)
        return res

    def getNeighbourCoords4d(self, sys, key):
        res = []
        for x in range(key[0] - 1, key[0] + 2):
            for y in range(key[1] - 1, key[1] + 2):
                for z in range(key[2] - 1, key[2] + 2):
                    for w in range(key[3] - 1, key[3] + 2):
                        res.append((x, y, z, w))
        res.remove(key)
        return res

    def iterate(self, nFunc):
        oldSystem = copy.deepcopy(self.system)
        allCoordList = []
        for key, value in oldSystem.items():
            if value == '.':
                continue
            nbList = nFunc(oldSystem, key)
            allCoordList = allCoordList + nbList + [key]
        allCoordsList = list(set(allCoordList))

        print("Number of neighbours: {}".format(len(allCoordsList)))
        for item in allCoordsList:
            isActive = oldSystem[item] == '#'
            nbList = nFunc(oldSystem, item)
            activeCount = self.countActiveInList(nbList, oldSystem)
            if isActive and not (activeCount == 2 or activeCount == 3):
                self.system[item] = '.'
            if not isActive and activeCount == 3:
                self.system[item] = '#'
    
    def resetSystem(self):
        self.system = copy.deepcopy(self.initSystem)

    def iterationDriver(self, maxIter, nFunc):
        for iter in range(maxIter):
            self.iterate(nFunc)
        return self.countActive()


