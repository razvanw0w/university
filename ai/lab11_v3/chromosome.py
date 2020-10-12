from math import sin, cos
from random import random, randint

maximumDepth = 5
parametersCount = 24
constants = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]
functions = ['+', '-', '*', 'sin', 'cos']
functionImplementations = {
    '+': lambda x, y: x + y,
    '-': lambda x, y: x - y,
    '*': lambda x, y: x * y,
    'sin': lambda x, y: sin(x),
    'cos': lambda x, y: cos(x)
}
functionCount = 5
classes = [
    'Slight-Left-Turn',
    'Move-Forward',
    'Slight-Right-Turn',
    'Sharp-Right-Turn'
]
classesCodes = {
    'Slight-Left-Turn': 0,
    'Move-Forward': 1,
    'Slight-Right-Turn': 2,
    'Sharp-Right-Turn': 3
}

class Chromosome:
    def __init__(self, treeDepth = maximumDepth):
        self.depth = treeDepth
        self.nodeType = [0 for _ in range(2 ** (self.depth + 1) - 1)]
        self.fitness = 0
        self.size = 0

    def build(self, position = 0, depth = 0):
        if (depth < self.depth or position == 0) and random() < 0.5:
            self.nodeType[position] = -randint(1, functionCount)
            firstSon = self.build(position + 1, depth + 1)
            secondSon = self.build(firstSon, depth + 1)
            return secondSon
        else:
            self.nodeType[position] = randint(1, parametersCount + len(constants))
            self.size = position + 1
            return position + 1

    def evaluate(self, position, trainData):
        node = self.nodeType[position]
        # terminal node!
        if node > 0:
            if node <= parametersCount:
                return trainData[node - 1], position
            else:
                return constants[node - parametersCount - 1], position
        # function!
        elif node < 0:
            function = functions[-node - 1]
            firstSon = self.evaluate(position + 1, trainData)
            secondSon = self.evaluate(firstSon[1] + 1, trainData)
            return functionImplementations[function](firstSon[0], secondSon[0]), secondSon[1]

    def getFitness(self, trainData, output):
        totalError = 0.0
        for i in range(len(trainData)):
            error = abs(classesCodes[output[i]] - self.evaluate(0, trainData[i])[0])
            totalError += error
        self.fitness = totalError

    def traverse(self, position):
        if self.nodeType[position] > 0:
            return position + 1
        else:
            return self.traverse(self.traverse(position + 1))

    @staticmethod
    def crossover(ch1, ch2):
        child = Chromosome()
        while True:
            startParent1 = randint(0, ch1.size - 1)
            endParent1 = ch1.traverse(startParent1)

            startParent2 = randint(0, ch2.size - 1)
            endParent2 = ch2.traverse(startParent2)
            if len(child.nodeType) > endParent1 + (endParent2 - startParent2 - 1) + (ch1.size - endParent1 - 1):
                break
        i = -1
        for i in range(startParent1):
            child.nodeType[i] = ch1.nodeType[i]
        for j in range(startParent2, endParent2):
            i += 1
            child.nodeType[i] = ch2.nodeType[j]
        for j in range(endParent1, ch1.size):
            i += 1
            child.nodeType[i] = ch1.nodeType[j]
        child.size = i + 1
        return child

    @staticmethod
    def mutate(ch):
        mutated = Chromosome()
        position = randint(0, ch.size - 1)
        mutated.nodeType = ch.nodeType[:]
        mutated.size = ch.size
        if mutated.nodeType[position] > 0:
            mutated.nodeType[position] = randint(1, parametersCount + len(constants))
        else:
            mutated.nodeType[position] = -randint(1, functionCount)
        return mutated
