import random
from copy import deepcopy

from PyQt5.QtCore import QThread, pyqtSignal


class PSO(QThread):
    finishedSignal = pyqtSignal('PyQt_PyObject')
    getPopulationSignal = pyqtSignal('PyQt_PyObject')
    currentIterationSignal = pyqtSignal('PyQt_PyObject')

    def __init__(self, generations, n, s, t, population, inertia, cognitive, social, neighbourhoodSize):
        QThread.__init__(self)
        self.__generations = generations
        self.__s = s
        self.__n = n
        self.__t = t
        self.__inertia = inertia
        self.__cognitive = cognitive
        self.__social = social
        self.__populationNumber = population
        self.__neighbourhoodSize = neighbourhoodSize

    def run(self):
        self.__population = Particle.createPopulation(self.__populationNumber, self.__n, self.__s, self.__t)
        self.__currentGeneration = 0
        neighbourhood = self.__getNeighbours()
        while self.__currentGeneration in range(self.__generations):
            self.__currentGeneration += 1
            inertia = self.__inertia / (self.__currentGeneration + 1)
            c1 = self.__cognitive
            c2 = self.__social

            maxFitness = max(self.__population, key=lambda x: x.getFitness()).getFitness()
            bestNeighbours = [0] * self.__populationNumber
            for i in range(self.__populationNumber):
                bestNeighbours[i] = max(neighbourhood[i], key=lambda x: self.__population[x].getFitness())

            # check for neighbourhoods stuck in local optimum
            for i in range(self.__populationNumber):
                equal = True
                if self.__population[i].getFitness() != self.__population[bestNeighbours[i]].getFitness():
                    equal = False
                if equal:
                    for neighbour in neighbourhood[i]:
                        if self.__population[neighbour] != self.__population[bestNeighbours[i]].getFitness():
                            equal = False
                            break
                if equal and self.__population[i].getFitness() == maxFitness:
                    self.__population[i].reinitialize()
                    for neighbour in neighbourhood[i]:
                        self.__population[neighbour].reinitialize()

            for k in range(self.__populationNumber):
                velocity = self.__population[k].getVelocity()
                bestNeighbourMatrix = self.__population[bestNeighbours[k]].getMatrix()
                currentMatrix = self.__population[k].getMatrix()
                currentBestMatrix = self.__population[k].getBestMatrix()
                for i in range(self.__n):
                    for j in range(self.__n):
                        # compute velocity
                        newVelocityS = inertia * velocity[i][j][0]
                        newVelocityS += c1 * random.random() * (currentBestMatrix[i][j][0] - currentMatrix[i][j][0])
                        newVelocityS += c2 * random.random() * (bestNeighbourMatrix[i][j][0] - currentMatrix[i][j][0])
                        newVelocityT = inertia * velocity[i][j][1]
                        newVelocityT += c1 * random.random() * (currentBestMatrix[i][j][1] - currentMatrix[i][j][1])
                        newVelocityT += c2 * random.random() * (bestNeighbourMatrix[i][j][1] - currentMatrix[i][j][1])
                        velocity[i][j] = (int(newVelocityS), int(newVelocityT))

                        # update position
                        newMatrixS = currentMatrix[i][j][0] + velocity[i][j][0]
                        newMatrixT = currentMatrix[i][j][1] + velocity[i][j][1]
                        if newMatrixS >= self.__n:
                            newMatrixS = self.__n - 1
                        if newMatrixT >= self.__n:
                            newMatrixT = self.__n - 1
                        if newMatrixS < 0:
                            newMatrixS = 0
                        if newMatrixT < 0:
                            newMatrixT = 0
                        currentMatrix[i][j] = (newMatrixS, newMatrixT)
                self.__population[k].setMatrix(currentMatrix)
                self.__population[k].setVelocity(velocity)
        self.finishedSignal.emit(self.__population)

    def __getNeighbours(self):
        self.__neighbourhoodSize = min(self.__neighbourhoodSize, self.__populationNumber)

        neighbours = []
        for i in range(self.__populationNumber):
            iNeighbours = []
            for j in range(self.__neighbourhoodSize):
                x = random.randint(0, self.__populationNumber - 1)
                while x in iNeighbours:
                    x = random.randint(0, self.__populationNumber - 1)
                iNeighbours.append(x)
            neighbours.append(iNeighbours)
        return neighbours

    def getPopulationUntilNow(self):
        self.getPopulationSignal.emit(self.__population)

    def getCurrentIteration(self):
        self.currentIterationSignal.emit(self.__currentGeneration)

    def stopRun(self):
        self.__currentGeneration = self.__generations


class Particle:
    def __init__(self, n, s, t):
        self.n = n
        self.s = s
        self.t = t
        self.reinitialize()
        self.evaluate()
        self.__bestFitness = self.__currentFitness
        self.__bestMatrix = deepcopy(self.__matrix)

    def reinitialize(self):
        self.__matrix = [[(random.randint(0, self.n - 1), random.randint(0, self.n - 1)) for j in range(self.n)] for i
                         in range(self.n)]
        self.__velocity = [
            [(random.randint(-self.n + 1, self.n - 1), random.randint(-self.n + 1, self.n - 1)) for j in range(self.n)]
            for i in range(self.n)]

    def evaluate(self):
        self.__currentFitness = self.fitness()

    @staticmethod
    def createPopulation(numberOfParticles, n, s, t):
        return [Particle(n, s, t) for i in range(numberOfParticles)]

    def isStuck(self):
        for line in self.__velocity:
            for item in line:
                if item != 0:
                    return False
        print("CPR!")
        return True

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

    def getFitness(self):
        return self.__currentFitness

    def getBestFitness(self):
        return self.__bestFitness

    def getMatrix(self):
        return deepcopy(self.__matrix)

    def getVelocity(self):
        return deepcopy(self.__velocity)

    def getBestMatrix(self):
        return deepcopy(self.__matrix)

    def setMatrix(self, newMatrix):
        self.__matrix = deepcopy(newMatrix)
        self.evaluate()
        if (self.__currentFitness > self.__bestFitness):
            self.__bestMatrix = deepcopy(self.__matrix)
            self.__bestFitness = self.__currentFitness

    def setVelocity(self, newVelocity):
        self.__velocity = deepcopy(newVelocity)

    def getBestMatrixString(self):
        answer = ""
        for i in range(self.n):
            for j in range(self.n):
                item = (self.s[self.__bestMatrix[i][j][0]], self.t[self.__bestMatrix[i][j][1]])
                answer += str(item) + " "
            answer += "\n"
        return answer

    def __str__(self):
        answer = ""
        for i in range(self.n):
            for j in range(self.n):
                item = (self.s[self.__matrix[i][j][0]], self.t[self.__matrix[i][j][1]])
                answer += str(item) + " "
            answer += "\n"
        return answer
