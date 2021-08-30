import numpy as np
#import itertools

def parse_input(input_str):
  retval = []
  for line in input_str.splitlines():
    l = line.split()
    retval.append([l[0], l[2]])

  return retval

def problem_part1(input, formula):
  finals = []
  form = formula
  for rep in input:
    start = 0
    while(form.find(rep[0],start) > -1):
      form = formula
      pos = form.find(rep[0], start)
      res = form[:start] + form[start:].replace(rep[0], rep[1], 1)
      if(not res in finals):
        finals.append(res)
      start = pos + 1

  return finals

def problem_part2(input, operations):
  que = [[input,0]]
  formula = que[0]

  count = 0
  while(formula != 'e'):
    count = count + 1
    formula = que[0][0]
    steps = que[0][1]
    que = que[1:] # pop next state

    if(count % 100 == 0):
      print(count, steps, len(formula), len(que))
      print(formula)
    for op in operations:
      start = 0
      end = len(formula)
      form = formula
      while(form.rfind(op[1], start, end) > -1):
        form = formula
        pos = form.rfind(op[1], start, end)
        res = form[:start] + form[start:].replace(op[1], op[0], 1)
        if(res == 'HF' or res == 'NAl' or res == "OMg"):
          return steps + 2
        que.append([res, steps + 1])
        end = pos
    que.sort(key = lambda x: len(x[0]))

  return 

input_txt = """Al => ThF
Al => ThRnFAr
B => BCa
B => TiB
B => TiRnFAr
Ca => CaCa
Ca => PB
Ca => PRnFAr
Ca => SiRnFYFAr
Ca => SiRnMgAr
Ca => SiTh
F => CaF
F => PMg
F => SiAl
H => CRnAlAr
H => CRnFYFYFAr
H => CRnFYMgAr
H => CRnMgYFAr
H => HCa
H => NRnFYFAr
H => NRnMgAr
H => NTh
H => OB
H => ORnFAr
Mg => BF
Mg => TiMg
N => CRnFAr
N => HSi
O => CRnFYFAr
O => CRnMgAr
O => HP
O => NRnFAr
O => OTi
P => CaP
P => PTi
P => SiRnFAr
Si => CaSi
Th => ThCa
Ti => BP
Ti => TiTi
e => HF
e => NAl
e => OMg"""

input_txt_ordered = """Al => ThF
H => CRnFYFYFAr
H => CRnFYMgAr
H => CRnMgYFAr
H => NRnFYFAr
O => CRnFYFAr
Ca => SiRnFYFAr
Ca => SiRnMgAr
Al => ThRnFAr
B => TiRnFAr
H => CRnAlAr
H => NRnMgAr
Ca => PRnFAr
P => SiRnFAr
H => ORnFAr
N => CRnFAr
O => NRnFAr
O => CRnMgAr
Ca => SiTh
F => CaF
F => PMg
F => SiAl
B => BCa
B => TiB
Ca => CaCa
Ti => TiTi
H => HCa
H => NTh
H => OB
Ca => PB
Mg => BF
Mg => TiMg
N => HSi
O => HP
O => OTi
P => CaP
P => PTi
Si => CaSi
Th => ThCa
Ti => BP"""

init_formula = "ORnPBPMgArCaCaCaSiThCaCaSiThCaCaPBSiRnFArRnFArCaCaSiThCaCaSiThCaCaCaCaCaCaSiRnFYFArSiRnMgArCaSiRnPTiTiBFYPBFArSiRnCaSiRnTiRnFArSiAlArPTiBPTiRnCaSiAlArCaPTiTiBPMgYFArPTiRnFArSiRnCaCaFArRnCaFArCaSiRnSiRnMgArFYCaSiRnMgArCaCaSiThPRnFArPBCaSiRnMgArCaCaSiThCaSiRnTiMgArFArSiThSiThCaCaSiRnMgArCaCaSiRnFArTiBPTiRnCaSiAlArCaPTiRnFArPBPBCaCaSiThCaPBSiThPRnFArSiThCaSiThCaSiThCaPTiBSiRnFYFArCaCaPRnFArPBCaCaPBSiRnTiRnFArCaPRnFArSiRnCaCaCaSiThCaRnCaFArYCaSiRnFArBCaCaCaSiThFArPBFArCaSiRnFArRnCaCaCaFArSiRnFArTiRnPMgArF"

input = parse_input(input_txt)

#print(len(problem_part1(input, init_formula)))

test_input_part2 = """H => HO
H => OH
O => HH"""

target_string = "HOH"

input_part2 = parse_input(input_txt_ordered)

#print(problem_part2(init_formula, input_part2))

count_tot = 0
count_Rn = 0
count_Ar = 0
count_Y = 0
for a in init_formula:
  if(a.isupper()):
    count_tot = count_tot + 1

print(init_formula)

while(init_formula.find("Rn") > -1):
  init_formula = init_formula.replace('Rn','',1)
  count_Rn = count_Rn + 1

print(init_formula)

while(init_formula.find("Ar") > -1):
  init_formula = init_formula.replace('Ar','',1)
  count_Ar = count_Ar + 1

print(init_formula)

while(init_formula.find("Y") > -1):
  init_formula = init_formula.replace('Y','',1)
  count_Y = count_Y + 1

print(init_formula)

print(count_tot, count_Rn, count_Ar, count_Y)
print(count_tot - 2*count_Rn - 2*count_Y - 1)





