import itertools
import random
from copy import deepcopy

from PyQt5.QtCore import QThread, pyqtSignal

from lab5.permutationutils import PermutationUtils


class ACO(QThread):
    finishedSignal = pyqtSignal('PyQt_PyObject')
    bestSolutionSignal = pyqtSignal('PyQt_PyObject')
    currentIterationSignal = pyqtSignal('PyQt_PyObject')

    def __init__(self, problem, epochs, population, alpha, beta, rho, q0):
        super().__init__()
        self.problem = problem
        self.epochs = epochs
        self.population = population
        self.alpha = alpha
        self.beta = beta
        self.rho = rho
        self.q0 = q0
        self.permutationSet = list(itertools.permutations(list(range(self.problem.n))))
        self.bestSolution = None
        self.currentEpoch = 0
        self.trace = {}
        self.running = True

    def epoch(self):
        ants = [Ant(self.problem) for i in range(self.population)]
        for i in range(2 * self.problem.n):
            for ant in ants:
                ant.addMove(self.q0, self.trace, self.alpha, self.beta)
        dTrace = [ant.fitness() for ant in ants]
        for i in range(len(self.problem.permutationSet)):
            for j in range(len(self.problem.permutationSet)):
                self.trace[(i, j)] = (1 - self.rho) * self.trace[(i, j)]
        for i in range(len(ants)):
            for j in range(len(ants[i].path) - 1):
                x = PermutationUtils.getPermutationIndex(ants[i].path[j])
                y = PermutationUtils.getPermutationIndex(ants[i].path[j + 1])
                self.trace[(x, y)] = self.trace[(x, y)] + dTrace[i]
        bestAnt = max(ants, key=lambda a: a.fitness())
        return bestAnt

    def run(self):
        for i in range(len(self.problem.permutationSet)):
            for j in range(len(self.problem.permutationSet)):
                self.trace[(i, j)] = 1

        print("started aco thread")
        while self.currentEpoch < self.epochs and self.running:
            self.currentEpoch += 1
            bestFromEpoch = deepcopy(self.epoch())
            if self.bestSolution is None:
                self.bestSolution = bestFromEpoch
                # print("updated")
            elif self.bestSolution.fitness() < bestFromEpoch.fitness():
                self.bestSolution = bestFromEpoch
                # print("updated")
        self.finishedSignal.emit(self.bestSolution)

    def getBestSolutionUntilNow(self):
        self.bestSolutionSignal.emit(self.bestSolution)

    def getCurrentIteration(self):
        self.currentIterationSignal.emit(self.currentEpoch)

    def stopRun(self):
        self.running = False


class Ant:
    def __init__(self, problem):
        self.problem = problem
        perm = list(range(self.problem.n))
        random.shuffle(perm)
        self.path = [perm]

    def distMove(self, newPerm):
        return PermutationUtils.distance(self.path[-1], newPerm)

    def addMove(self, q0, trace, alpha, beta):
        lastState = self.path[-1]
        lastStateIndex = PermutationUtils.getPermutationIndex(lastState)
        p = [self.distMove(k) for k in self.problem.permutationSet]
        p = [(trace[(lastStateIndex, i)] ** alpha) * (1 / p[i] ** beta) for i in range(len(p))]
        rnd = random.random()
        if rnd < q0:
            maximum = -1
            bestPerm = []
            for i in range(len(p)):
                if p[i] > maximum:
                    maximum = p[i]
                    bestPerm = self.problem.permutationSet[i]
            self.path.append(deepcopy(bestPerm))
        else:
            s = sum(p)
            if s == 0:
                self.path.append(random.choice(self.problem.permutationSet))
            else:
                p = [x / s for x in p]
                p = [sum(p[0: i + 1]) for i in range(len(p))]
                rng = random.random()
                for i in range(len(p)):
                    if rng < p[i]:
                        self.path.append(self.problem.permutationSet[i])
                        break

    def getSolutionMatrix(self):
        matrix = [[(0, 0) for i in range(self.problem.n)] for j in range(self.problem.n)]
        for i in range(self.problem.n):
            for j in range(self.problem.n):
                matrix[i][j] = (self.path[i][j], self.path[i + self.problem.n][j])
        return matrix

    def fitness(self):
        matrix = self.getSolutionMatrix()
        fitness = 1
        # decrease points for each bad element from a bad permutation 4 * n
        # decrease points for each duplicate element in the matrix n * n
        factor = 1 / (4 * self.problem.n + self.problem.n * self.problem.n)
        badElems = 0
        appearing = {}
        for i in range(self.problem.n):
            for j in range(self.problem.n):
                elem = matrix[i][j]
                if elem not in appearing.keys():
                    appearing[elem] = 1
                else:
                    badElems += 1
        fitness -= factor * badElems
        for i in range(self.problem.n):
            rowS = {}
            rowT = {}
            badElemsS = 0
            badElemsT = 0
            for j in range(self.problem.n):
                elem1 = matrix[i][j][0]
                elem2 = matrix[i][j][1]
                if elem1 not in rowS.keys():
                    rowS[elem1] = 1
                else:
                    badElemsS += 1
                if elem2 not in rowT.keys():
                    rowT[elem2] = 1
                else:
                    badElemsT += 1
            fitness -= factor * (badElemsS + badElemsT)
        for j in range(self.problem.n):
            rowS = {}
            rowT = {}
            badElemsS = 0
            badElemsT = 0
            for i in range(self.problem.n):
                elem1 = matrix[i][j][0]
                elem2 = matrix[i][j][1]
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
        matrix = self.getSolutionMatrix()
        answer = ""
        for line in matrix:
            for item in line:
                realItem = (self.problem.s[item[0]], self.problem.t[item[1]])
                answer += str(realItem) + " "
            answer += '\n'
        return answer
