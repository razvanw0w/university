from random import randint


def getShapes():
    lineShape = [(0, 0), (0, 1), (0, 2), (0, 3)]
    uShape = [(0, 0), (1, 0), (1, 1), (1, 2), (0, 2)]
    lShape = [(0, 0), (1, 0), (1, 1), (1, 2)]
    reverseLShape = [(0, 0), (0, 1), (0, 2), (1, 2)]
    tShape = [(0, 0), (0, 1), (-1, 1), (0, 2)]
    return [lineShape, uShape, lShape, reverseLShape, tShape]


def isInside(i, j, x, y):
    return 0 <= i < x and 0 <= j < y


def trySolve(shapes, x, y):
    matrix = [[0 for i in range(y)] for j in range(x)]
    for k in range(len(shapes)):
        shape = shapes[k]
        i = randint(0, x)
        j = randint(0, y)
        for cell in shape:
            offsetI = cell[0]
            offsetJ = cell[1]
            if isInside(i + offsetI, j + offsetJ, x, y):
                matrix[i + offsetI][j + offsetJ] = k + 1
    return matrix


def getNumberOfOccurences(shapes, matrix):
    occurences = {0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0}
    for line in matrix:
        for item in line:
            occurences[item] += 1
    return occurences


def solution(shapes, matrix):
    occurences = getNumberOfOccurences(shapes, matrix)
    for k in range(len(shapes)):
        if occurences[k + 1] != len(shapes[k]):
            return False
    return True


def printSolution(matrix):
    for line in matrix:
        for item in line:
            print(item, end = ' ')
        print()


while True:
    trials = int(input("How many trials?: "))
    x, y = [int(t) for t in input("How many rows/columns?: ").strip().split()]
    shapes = getShapes()
    for i in range(trials):
        print("Trial number " + str(i))
        result = trySolve(shapes, x, y)
        if solution(shapes, result):
            print("Found solution!")
            printSolution(result)
            break