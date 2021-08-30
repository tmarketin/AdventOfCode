import re

def loadFromFile(fname):
    with open(fname, 'r') as fp:
        res = [[int(k) if str.isdigit(k) else k for k in list(re.sub(' ', '', s.strip()))] for s in fp]
    return res

def operate(lop, op, rop):
    if op == '+':
        return lop + rop
    elif op == '*':
        return lop*rop
    else:
        print("Unexpected operator")
    return 0

def evaluateEqualPrecedence(expr):
    operatorStack = []
    operandStack = []
    for item in expr:
        if item in [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]:
            if len(operatorStack) > 0 and operatorStack[-1] in ['+', '*']:
                left = operandStack.pop()
                operator = operatorStack.pop()
                operandStack.append(operate(left, operator, item))
            else:
                operandStack.append(item)
        elif item in ['+', '*', '(']:
            operatorStack.append(item)
        elif item == ')':
            if operatorStack[-1] == '(':
                operatorStack.pop()
                if len(operatorStack) > 0 and operatorStack[-1] in ['+', '*']:
                    rop = operandStack.pop()
                    lop = operandStack.pop()
                    operator = operatorStack.pop()
                    operandStack.append(operate(lop, operator, rop))
            else:
                print("Error, closing bracket not closing")
#        print(item, operatorStack, operandStack)
    if len(operatorStack) > 0:
        print("Error, remaining operators")
    if len(operandStack) > 1:
        print("Error, too many operands left")
    return operandStack[0]

def evaluateDifferentPrecedence(expr):
    operatorStack = []
    operandStack = []
    for item in expr:
        if item in [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]:
            if len(operatorStack) > 0 and operatorStack[-1] == '+':
                left = operandStack.pop()
                operator = operatorStack.pop()
                operandStack.append(operate(left, operator, item))
            else:
                operandStack.append(item)
        elif item in ['+', '*', '(']:
            operatorStack.append(item)
        elif item == ')':
            while operatorStack[-1] != '(':
                rop = operandStack.pop()
                operator = operatorStack.pop()
                lop = operandStack.pop()
                operandStack.append(operate(lop, operator, rop))

            operatorStack.pop()
            if len(operatorStack) > 0 and operatorStack[-1] == '+':
                rop = operandStack.pop()
                lop = operandStack.pop()
                operator = operatorStack.pop()
                operandStack.append(operate(lop, operator, rop))
#        print(item, operatorStack, operandStack)
    while operatorStack:
        rop = operandStack.pop()
        operator = operatorStack.pop()
        lop = operandStack.pop()
        operandStack.append(operate(lop, operator, rop))
    if len(operatorStack) > 0:
        print("Error, remaining operators: ", operatorStack)
    if len(operandStack) > 1:
        print("Error, too many operands left: ", operandStack)
    return operandStack[0]

def solution(input, evalFun):
    totalSum = 0
    for expr in input:
        res = evalFun(expr)
        totalSum = totalSum + res
    return totalSum

input = loadFromFile("input_day18.dat")

print("Solution to part 1: {}".format(solution(input, evaluateEqualPrecedence)))
print("Solution to part 1: {}".format(solution(input, evaluateDifferentPrecedence)))