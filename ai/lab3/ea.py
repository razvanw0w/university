import random
from copy import deepcopy

from PyQt5.QtCore import QThread, pyqtSignal


class EA(QThread):
    finishedSignal = pyqtSignal('PyQt_PyObject')
    getPopulationSignal = pyqtSignal('PyQt_PyObject')
    currentIterationSignal = pyqtSignal('PyQt_PyObject')

    def __init__(self, generations, n, s, t, probability, population):
        QThread.__init__(self)
        self.__generations = generations
        self.__s = s
        self.__n = n
        self.__t = t
        self.__mutation = probability
        self.__populationNumber = population

    def run(self):
        self.__population = EAIndividual.getInitialPopulation(self.__n, self.__s, self.__t, self.__populationNumber)
        self.__currentGeneration = 0
        while self.__currentGeneration in range(self.__generations):
            self.__currentGeneration += 1
            index1 = random.randint(0, self.__populationNumber - 1)
            index2 = random.randint(0, self.__populationNumber - 1)
            guy1 = self.__population[index1]
            guy2 = self.__population[index2]
            f1 = guy1.fitness()
            f2 = guy2.fitness()

            child = EAIndividual.crossover(guy1, guy2)
            child.mutate(self.__mutation)
            fc = child.fitness()
            if f1 <= f2 and f1 < fc:
                self.__population[index1] = child
            if f2 <= f1 and f2 < fc:
                self.__population[index2] = child
        self.finishedSignal.emit(self.__population)

    def getPopulationUntilNow(self):
        self.getPopulationSignal.emit(self.__population)

    def getCurrentIteration(self):
        self.currentIterationSignal.emit(self.__currentGeneration)

    def stopRun(self):
        self.__currentGeneration = self.__generations

class EAIndividual:
    def __init__(self, n, s, t):
        self.n = n
        self.s = s
        self.t = t
        self.__matrix = [[(0, 0) for i in range(n)] for j in range(n)]
        for i in range(n):
            for j in range(n):
                x = random.choice(s)
                y = random.choice(t)
                self.__matrix[i][j] = (x, y)

    def getMatrix(self):
        return deepcopy(self.__matrix)

    def setMatrix(self, matrix):
        self.__matrix = matrix

    def mutate(self, probability):
        choice = random.random()
        if choice <= probability:
            i = random.randint(0, self.n - 1)
            j = random.randint(0, self.n - 1)
            x = random.choice(self.s)
            y = random.choice(self.t)
            self.__matrix[i][j] = (x, y)

    @staticmethod
    def getInitialPopulation(n, s, t, count):
        return [EAIndividual(n, s, t) for i in range(count)]

    @staticmethod
    def crossover(guy1, guy2):
        matrix1 = guy1.getMatrix()
        matrix2 = guy2.getMatrix()
        splitter = random.randint(0, guy1.n - 2)
        for i in range(guy1.n):
            for j in range(splitter + 1, guy1.n):
                matrix1[i][j] = matrix2[i][j]
        individual = EAIndividual(guy1.n, guy1.s, guy1.t)
        return individual

    def fitness(self):
        fitness = 1
        # decrease points for each bad element from a bad permutation 4 * n
        # decrease points for each duplicate element in the matrix n * n
        factor = 1 / (4 * self.n + self.n * self.n)
        badElems = 0
        appearing = {}
        for i in range(self.n):
            for j in range(self.n):
                elem = self.__matrix[i][j]
                if elem not in appearing.keys():
                    appearing[elem] = 1
                else:
                    badElems += 1
        fitness -= factor * badElems
        for i in range(self.n):
            rowS = {}
            rowT = {}
            badElemsS = 0
            badElemsT = 0
            for j in range(self.n):
                elem1 = self.__matrix[i][j][0]
                elem2 = self.__matrix[i][j][1]
                if elem1 not in rowS.keys():
                    rowS[elem1] = 1
                else:
                    badElemsS += 1
                if elem2 not in rowT.keys():
                    rowT[elem2] = 1
                else:
                    badElemsT += 1
            fitness -= factor * (badElemsS + badElemsT)
        for j in range(self.n):
            rowS = {}
            rowT = {}
            badElemsS = 0
            badElemsT = 0
            for i in range(self.n):
                elem1 = self.__matrix[i][j][0]
                elem2 = self.__matrix[i][j][1]
                if elem1 not in rowS.keys():
                    rowS[elem1] = 1
                else:
                    badElemsS += 1
                if elem2 not in rowT.keys():
                    rowT[elem2] = 1
                else:
                    badElemsT += 1
            fitness -= factor * (badElemsS + badElemsT)
        return fitness

    def __str__(self):
        answer = ""
        for line in self.__matrix:
            for item in line:
                answer += str(item) + " "
            answer += "\n"
        return answer
