import itertools
import numpy as np

def load_input(fname):
  retval = []
  tmpdict = {'gain': +1, 'lose': -1}
  with open(fname,"r") as fp:
    for line in fp:
      l = line.strip(".\n").split()
      retval.append([ l[0], l[10], tmpdict[l[2]]*int(l[3]) ])
  return retval

def gen_list_names(input):
  retval = []
  for line in input:
    if(not line[0] in retval):
      retval.append(line[0])
    if(not line[1] in retval):
      retval.append(line[1])

  return sorted(retval)

def gen_index_dict(names):
  retval = {}
  tmpidx = 0
  for n in names:
    retval[n] = tmpidx
    tmpidx = tmpidx + 1

  return retval

def gen_happy_matrix(input, names, idx):
  ndim = len(names)
  hmat = np.zeros((ndim, ndim))

  for line in input:
    hmat[idx[line[0]],idx[line[1]]] = line[2]

  return hmat

def calc_cost(pos, happiness, idx):
  s = 0
  for n in range(len(pos) - 1):
    s = s + happiness[idx[pos[n]],idx[pos[n+1]]] + happiness[idx[pos[n+1]],idx[pos[n]]]
  s = s + happiness[idx[pos[0]],idx[pos[len(pos) - 1]]] + happiness[idx[pos[len(pos) - 1]],idx[pos[0]]]

  return s

def find_optimal(names, happiness, idx):
  positions = list(itertools.permutations(names[1:]))

  pmax = [names[0]] + list(positions[0])
  cmax = calc_cost(pmax, happiness, idx)
  for p in positions:
    pos = [names[0]] + list(p)
    cost = calc_cost(pos, happiness, idx)
    if(cost > cmax):
      pmax = pos
      cmax = cost

  print(pmax, cmax)
  return

input = load_input("day13.dat")
names = gen_list_names(input)
idx = gen_index_dict(names)
happiness = gen_happy_matrix(input, names, idx)

find_optimal(names, happiness, idx)

names.append('You')
idx['You'] = 8
happiness = np.concatenate((happiness, np.zeros((8,1))), axis = 1)
happiness = np.concatenate((happiness, np.zeros((1,9))), axis = 0)
find_optimal(names, happiness, idx)

