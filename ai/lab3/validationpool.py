from PyQt5.QtCore import pyqtSignal, QThread

from lab3.ea import EA
from lab3.pso import PSO


class ValidationPool(QThread):
    poolFinishedSignal = pyqtSignal('PyQt_PyObject')

    def __init__(self, type):
        QThread.__init__(self)
        self.__type = type
        self.__threads = []
        self.__fitnesses = []
        self.__count = 0

    def fillEAThreads(self):
        self.__threads = [EA(1000, 3, [1, 2, 3], [1, 2, 3], 0.5, 40) for i in range(30)]
        for i in range(30):
            self.__threads[i].finishedSignal.connect(self.finishedThread)

    def fillPSOThreads(self):
        self.__threads = [PSO(100, 3, [1, 2, 3], [1, 2, 3], 40, 1, 2.5, 1, 10) for i in range(30)]
        for i in range(30):
            self.__threads[i].finishedSignal.connect(self.finishedThread)

    def run(self):
        self.__count = 0
        self.__fitnesses = []
        for i in range(30):
            self.__threads[i].start()

    def finishedThread(self, population):
        if self.__type == "EA":
            self.__fitnesses.append(max(population, key=lambda x: x.fitness()).fitness())
        else:
            self.__fitnesses.append(max(population, key=lambda x: x.getBestFitness()).getBestFitness())
        self.__count += 1
        print("new thread finished", self.__count)
        if self.__count == 30:
            self.poolFinishedSignal.emit(self.__fitnesses)
