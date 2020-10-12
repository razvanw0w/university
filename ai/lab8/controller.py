import random
from lab8.logic import *
from lab8.repository import *
from lab8.network import NeuralNetwork

class Controller:
    def __init__(self, repo):
        self.repo = repo
        self.network = NeuralNetwork(3)

    def train(self, iterations):
        points = self.repo.fetchEntries()
        for i in range(iterations):
            self.network.trainInputs(points)
        print(self.network.loss)
        return self.network.loss

    def test(self):
        results = []
        points = self.repo.fetchEntries()
        for entry in points:
            realValue = entry[-1]
            computedValue = self.network.feedForward(entry)
            results.append((entry[:5], entry[-1], computedValue, abs(realValue - computedValue)))
        return results