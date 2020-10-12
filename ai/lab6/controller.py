from lab6.dt import DTNode
import math

from lab6.logic import *

class Controller:
    def __init__(self, repository):
        self.repository = repository
        self.trainRatio = 0.85

    def runDecisionTree(self):
        train, test = self.repository.getTrainAndTestData(self.trainRatio)
        dt = DT.createDecisionTree(train)
        tested = Tester.testInstances(test, dt)
        return Tester.getAccuracy(tested)
