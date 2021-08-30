import copy
import re

def loadFromFile(fname):
    rules = {}
    msgs = []
    with open(fname, 'r') as fp:
        lines = [line.strip() for line in fp]
        for line in lines:
            if not line:
                continue
            if line.find(':') == -1:
                msgs.append(line)
            else:
                splitLine = re.sub('[:"]', '', line).strip().split()
                rules[int(splitLine[0])] = splitLine[1:]
    parseRules(rules)
    return rules, msgs

def parseRules(rules):
    for key, value in rules.items():
        if value[0] in ['a', 'b']:
            rules[key] = [value]
            continue
        if '|' not in value:
            rules[key] = [[int(k) for k in value]]
        else:
            val = []
            pipeIdx = value.index('|')
            val.append([int(k) for k in value[:pipeIdx]])
            val.append([int(k) for k in value[pipeIdx + 1:]])
            rules[key] = val

def allChar(rule):
    res = True
    for item in rule:
        if type(item) != str:
            res = False
    return res

def findSolvedRules(rules):
    solved = []
    for key, value in rules.items():
        isAllChar = True
        for subrule in value:
            if not allChar(subrule):
                isAllChar = False
        if isAllChar:
            solved.append(key)
    return solved

def appendToAll(target, source):
    for item in target:
        item.extend(source)

def appendAllComb(target, source):
#    print("Append all - target: {}, source: {}".format(target, source))
    newTarget = []
    for itemSource in source:
        targetCopy = copy.deepcopy(target)
        for itemTarget in targetCopy:
            itemTarget.extend(itemSource)
        newTarget.extend(targetCopy)
    return newTarget

def applyRule(key, rules):
    resRule = []
    for subrule in rules[key]:
        resSubrule = []
        for item in subrule:
            if resSubrule == []:
                resSubrule.extend(rules[item])
            else:
                resSubrule = appendAllComb(resSubrule, rules[item])
        resRule.extend([[''.join(subList)] for subList in resSubrule])
#    print("Applied rule {}, init: {}, result: {}".format(key, rules[key], resRule))
    rules[key] = resRule

def allRulesSolved(value, solvedRules):
    for subrule in value:
        for item in subrule:
            if not item in solvedRules:
                return False
    return True

def applyRules(rules, solvedRules):
    res = []
    for key, value in rules.items():
        if key in solvedRules:
            continue
        if allRulesSolved(value, solvedRules):
            applyRule(key, rules)
            res.append(key)
    return res

def evalRules(rules):
    appliedRules = []
    solvedRules = findSolvedRules(rules)
    while 0 not in solvedRules:
        print("Solved rules: {}, total: {}".format(sorted(solvedRules), len(solvedRules)))
        appliedRules = applyRules(rules, solvedRules)
        print("Applied rules: {}".format(appliedRules))
        solvedRules = findSolvedRules(rules)

def part1(rule0, msgs):
    flatRule = [item for sublist in rule0 for item in sublist]
    return sum(1 for msg in msgs if msg in flatRule)

rules, msgs = loadFromFile("input_day19.dat")

evalRules(rules)
print("Solution to part 1: {}".format(part1(rules[0], msgs)))
