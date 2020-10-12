import random
from lab7.logic import *
from lab7.repository import *

class Controller:
    def __init__(self, repo):
        self.repo = repo
        self.coefficients = [random.randint(-10, 10) for i in range(6)]

    def train(self, iterations):
        points = self.repo.fetchEntries()
        self.coefficients = getBestCoefficients(points, self.coefficients, 0.001, iterations)

    def get(self):
        return self.coefficients[:]

    def test(self):
        results = []
        points = self.repo.fetchEntries()
        for entry in points:
            results.append((entry[:5], entry[-1], getFunctionValue(entry, self.coefficients), computeSimpleError(entry, self.coefficients)))
        return results