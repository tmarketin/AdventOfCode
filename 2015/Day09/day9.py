import itertools
import numpy as np

def load_file(fname):
  fp = open(fname,"r")
  a = []
  for line in fp:
    a.append([line.split()[0], line.split()[2], int(line.split()[4])])

  return a

def list_cities(ll):
  retval = []
  for line in ll:
    if(not line[0] in retval):
      retval.append(line[0])
    if(not line[1] in retval):
      retval.append(line[1])

  return sorted(retval)

def find_distance(path, dist, idx):
  s = 0
  for a in range(len(path) - 1):
    s = s + dist[idx[path[a]],idx[path[a+1]]]

  return s

input = load_file("day9.dat")
cities = list_cities(input)

ndim = len(cities)
dist = np.zeros((ndim, ndim))
idx = {}
tmpidx = 0
for c in cities:
  idx[c] = tmpidx
  tmpidx = tmpidx + 1

for line in input:
  dist[idx[line[0]],idx[line[1]]] = line[2]
  dist[idx[line[1]],idx[line[0]]] = line[2]

print(idx)
print(dist)

paths = list(itertools.permutations(cities))

pmin = paths[0]
dmin = find_distance(pmin, dist, idx)
pmax = pmin
dmax = dmin
for p in paths:
  d = find_distance(p, dist, idx)
  if(dmin > d):
    pmin = p
    dmin = d
  if(dmax < d):
    pmax = p
    dmax = d

print(pmin, dmin)
print(pmax, dmax)