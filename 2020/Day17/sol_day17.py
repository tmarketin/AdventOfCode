from conway3d import Conway 

conway = Conway("input_day17.dat")

print("Solution to part 1: {}".format(conway.iterationDriver(6, conway.getNeighbourCoords3d)))

conway.resetSystem()
print("Solution to part 2: {}".format(conway.iterationDriver(6, conway.getNeighbourCoords4d)))