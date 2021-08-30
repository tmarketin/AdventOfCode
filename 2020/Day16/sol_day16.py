import re

def loadFromFile(fname):
    rules = {}
    tickets = []
    with open(fname, 'r') as fp:
        lines = [line.strip() for line in fp]
        idx = 0
        while lines[idx]:
            line = lines[idx].strip().split(':')
            fieldName = line[0]
            splitLine = re.sub('-', ' ', line[1].strip()).split()
            rules[fieldName] = {'min1': int(splitLine[0]), 'max1': int(splitLine[1]), 'min2': int(splitLine[3]), 'max2': int(splitLine[4])}
            idx = idx + 1
        idx = idx + 2
        myTicket = [int(k) for k in lines[idx].strip().split(',')]

        idx = idx + 3
        for line in lines[idx:]:
            tickets.append([int(k) for k in line.strip().split(',')])

    return rules, tickets, myTicket

def validateTicket(ticket, rules):
    count = 0
    isTicketValid = True
    for field in ticket:
        isValid = False
        for key, value in rules.items():
            if (field >= value['min1'] and field <= value['max1']) or (field >= value['min2'] and field <= value['max2']):
                isValid = True
        if not isValid:
            count = count + field
            isTicketValid = False
    return isTicketValid, count

def part1(rules, tickets):
    count = 0
    validTickets = []
    for ticket in tickets:
        isValid, invalidValues = validateTicket(ticket, rules)
        count = count + invalidValues
        if isValid:
            validTickets.append(ticket)
    return count, validTickets

def isValidCategory(value, rule):
    if (value >= rule['min1'] and value <= rule['max1']) or (value >= rule['min2'] and value <= rule['max2']):
        return True
    return False

def removeCategoryFromOtherOptions(options, fieldIdx):
    ruleKey = options[fieldIdx][0]
    for idx in range(len(options)):
        if idx != fieldIdx and ruleKey in options[idx]:
            options[idx].remove(ruleKey)

def printOptions(options):
    for key, values in options.items():
        print(key, values)

def eliminateRules(rules, options, tickets):
    noFields = len(options)
    for fieldIdx in range(noFields):
        for ticket in validTickets:
            for ruleKey, ruleValue in rules.items():
                if not isValidCategory(ticket[fieldIdx], ruleValue) and ruleKey in options[fieldIdx]:
#                    print("FieldIdx: {}, ruleKey: {}, ruleSet: {}, ticket: {}, options: {}".format(fieldIdx, ruleKey, ruleValue, ticket, options[fieldIdx]))
                    options[fieldIdx].remove(ruleKey)

def isFilteringDone(options):
    isDone = True
    for key, value in options.items():
        if len(value) > 1:
            isDone = False
            break
    return isDone

def filterSingles(options):
    noFields = len(options)
    while not isFilteringDone(options):
        for idx in range(noFields):
            if len(options[idx]) == 1:
                removeCategoryFromOtherOptions(options, idx)

def part2(rules, validTickets, myTicket):
    print("Number of valid tickets: ", len(validTickets))
    ruleNames = list(rules.keys())
    noFields = len(myTicket)
    options = {}
    for idx in range(noFields):
        options[idx] = ruleNames.copy()
    
    eliminateRules(rules, options, validTickets)
    filterSingles(options)

    res = 1
    for key, value in options.items():
        if value[0].startswith('departure'):
            res = res*myTicket[key]

    for idx in range(len(options)):
        print(idx, ' : ', options[idx][0], ' : ', myTicket[idx])

    return res

rules, tickets, myTicket = loadFromFile("input_day16.dat")

part1Sol, validTickets = part1(rules, tickets)
print("Solution to part 1: {}".format(part1Sol))
print("Solution to part 2: {}".format(part2(rules, validTickets, myTicket)))