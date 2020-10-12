import random
from copy import deepcopy

from PyQt5.QtCore import QThread, pyqtSignal


class HC(QThread):
    finishedSignal = pyqtSignal('PyQt_PyObject')
    bestSolutionSignal = pyqtSignal('PyQt_PyObject')
    currentIterationSignal = pyqtSignal('PyQt_PyObject')

    def __init__(self, runs, n, s, t):
        QThread.__init__(self)
        self.__runs = runs
        self.__n = n
        self.__s = s
        self.__t = t
        self.__state = None
        self.__currentIteration = 0

    def run(self):
        self.__state = HCState.getInitialState(self.__n, self.__s, self.__t)
        print(str(self.__state))
        print(self.__state.fitness())
        self.__currentIteration = 0
        while self.__currentIteration in range(self.__runs):
            if self.__state.fitness() == 1:
                break
            self.__currentIteration += 1
            best = self.__state.getBestNeighbour()
            if self.__state.fitness() < best.fitness():
                print("updated", self.__currentIteration)
                self.__state = best
        self.finishedSignal.emit(self.__state)

    def getBestSolutionUntilNow(self):
        self.bestSolutionSignal.emit(self.__state)

    def getCurrentIteration(self):
        self.currentIterationSignal.emit(self.__currentIteration)

    def stopRun(self):
        self.__currentIteration = self.__runs


class HCState:
    def __init__(self, n, s, t):
        self.__n = n
        self.__matrix = [[(0, 0) for i in range(n)] for j in range(n)]
        self.__s = s
        self.__t = t

    def getMatrix(self):
        return self.__matrix[:]

    def setMatrix(self, matrix):
        self.__matrix = matrix[:]

    def fitness(self):
        fitness = 1
        # decrease points for each bad element from a bad permutation 4 * n
        # decrease points for each duplicate element in the matrix n * n
        factor = 1 / (4 * self.__n + self.__n * self.__n)
        badElems = 0
        appearing = {}
        for i in range(self.__n):
            for j in range(self.__n):
                elem = self.__matrix[i][j]
                if elem not in appearing.keys():
                    appearing[elem] = 1
                else:
                    badElems += 1
        fitness -= factor * badElems
        for i in range(self.__n):
            rowS = {}
            rowT = {}
            badElemsS = 0
            badElemsT = 0
            for j in range(self.__n):
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
        for j in range(self.__n):
            rowS = {}
            rowT = {}
            badElemsS = 0
            badElemsT = 0
            for i in range(self.__n):
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

    @staticmethod
    def getInitialState(n, s, t):
        state = HCState(n, s, t)
        matrix = [[(0, 0) for i in range(n)] for j in range(n)]
        for i in range(n):
            for j in range(n):
                x = random.choice(s)
                y = random.choice(t)
                matrix[i][j] = (x, y)
        state.setMatrix(matrix)
        return state

    def getBestNeighbour(self):
        bestFitness = -1
        bestState = HCState(self.__n, self.__s, self.__t)
        matrix = deepcopy(self.__matrix)
        for i in range(self.__n):
            for j in range(self.__n):
                state1 = HCState(self.__n, self.__s, self.__t)
                state2 = HCState(self.__n, self.__s, self.__t)
                state3 = HCState(self.__n, self.__s, self.__t)
                state4 = HCState(self.__n, self.__s, self.__t)
                oldS = matrix[i][j][0]
                oldT = matrix[i][j][1]
                indexS = self.__s.index(oldS)
                indexT = self.__t.index(oldT)
                indexSLow = indexS - 1
                indexTLow = indexT - 1
                indexSHigh = indexS + 1 if indexS < self.__n - 1 else indexS + 1 - self.__n
                indexTHigh = indexT + 1 if indexT < self.__n - 1 else indexT + 1 - self.__n
                matrix[i][j] = (self.__s[indexSLow], oldT)
                state1.setMatrix(deepcopy(matrix))
                matrix[i][j] = (self.__s[indexSHigh], oldT)
                state2.setMatrix(deepcopy(matrix))
                matrix[i][j] = (oldS, self.__t[indexTLow])
                state3.setMatrix(deepcopy(matrix))
                matrix[i][j] = (oldS, self.__t[indexTHigh])
                state4.setMatrix(deepcopy(matrix))
                matrix[i][j] = (oldS, oldT)
                f1, f2, f3, f4 = state1.fitness(), state2.fitness(), state3.fitness(), state4.fitness()
                if f1 > bestFitness:
                    bestFitness = f1
                    bestState = state1
                if f2 > bestFitness:
                    bestFitness = f2
                    bestState = state2
                if f3 > bestFitness:
                    bestFitness = f3
                    bestState = state3
                if f4 > bestFitness:
                    bestFitness = f4
                    bestState = state4
        return bestState

    # def getBestNeighbour(self):
    #     bestFitness = -1
    #     bestState = HCState(self.__n, self.__s, self.__t)
    #     for k in range(5000):
    #         # if k % 500 == 0:
    #         #     print("bestNeighbour", k)
    #         state = HCState(self.__n, self.__s, self.__t)
    #         firstOrSecond = random.randint(0, 1)
    #         matrix = self.__matrix[:]
    #         index = random.randint(0, self.__n - 1)
    #         index1 = random.randint(0, self.__n - 1)
    #         index2 = random.randint(0, self.__n - 1)
    #         while index1 == index2:
    #             index2 = random.randint(0, self.__n - 1)
    #         elem1 = elem2 = None
    #         if firstOrSecond == 0:
    #             elem1 = (matrix[index][index2][0], matrix[index][index1][1])
    #             elem2 = (matrix[index][index1][0], matrix[index][index2][1])
    #         else:
    #             elem1 = (matrix[index][index1][0], matrix[index][index2][1])
    #             elem2 = (matrix[index][index2][0], matrix[index][index1][1])
    #         matrix[index][index1] = elem1
    #         matrix[index][index2] = elem2
    #
    #         state.setMatrix(matrix)
    #         fitness = state.fitness()
    #         if bestFitness <= fitness:
    #             bestFitness = fitness
    #             bestState = state
    #     return bestState
    def __str__(self):
        answer = ""
        for line in self.__matrix:
            for item in line:
                answer += str(item) + " "
            answer += "\n"
        return answer
