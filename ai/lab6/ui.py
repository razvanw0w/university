from lab6.controller import Controller

class UI:
    def __init__(self, controller):
        self.controller = controller

    def run(self):
        numberOfTrials = int(input("Number of trials: "))
        maxAccuracy = 0
        for i in range(numberOfTrials):
            accuracy = self.controller.runDecisionTree()
            print(i, str(accuracy) + '%')
            maxAccuracy = max(maxAccuracy, accuracy)
        print('Best:', str(maxAccuracy) + '%')