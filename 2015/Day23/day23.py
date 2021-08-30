# -*- coding: utf-8 -*-

def main():
  range = []
  
  f = open("day23.dat","r")  
  for line in f:
    range.append(line.strip().split(' '))
  f.close()
  
  val = {'a': 1, 'b': 0}
  count = 0
  next = 0
  while (next < len(range)):
    count = count + 1
    print(count,next,range[next],val['a'],val['b'])
    if range[next][0] == 'hlf':
      val[range[next][1]] = val[range[next][1]]//2
      next = next + 1
    elif range[next][0] == 'tpl':
      val[range[next][1]] = 3*val[range[next][1]]
      next = next + 1
    elif range[next][0] == 'inc':
      val[range[next][1]] = val[range[next][1]] + 1
      next = next + 1
    elif range[next][0] == 'jmp':
      next = next + int(range[next][1])
    elif range[next][0] == 'jie':
      if val[range[next][1]] % 2 == 0:
        next = next + int(range[next][2])
      else:
        next = next + 1
    elif range[next][0] == 'jio':
      if val[range[next][1]] == 1:
        next = next + int(range[next][2])
      else:
        next = next + 1
  
  print(count,val['a'],val['b'])

  
if __name__=='__main__':
  main()