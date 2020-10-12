from PyQt5.QtCore import pyqtSignal, QThread

from lab5.aco import ACO
from lab5.problem import Problem


class ValidationPool(QThread):
    poolFinishedSignal = pyqtSignal('PyQt_PyObject')

    def __init__(self):
        QThread.__init__(self)
        self.__threads = []
        self.__fitnesses = []
        self.__count = 0

    def fillACOThreads(self):
        self.__threads = [ACO(Problem(3, [1, 2, 3], [1, 2, 3]), 100, 40, 1.9, 0.9, 0.05, 0.5) for i in range(30)]
        for i in range(30):
            self.__threads[i].finishedSignal.connect(self.finishedThread)

    def run(self):
        self.__count = 0
        self.__fitnesses = []
        print("starting threads")
        for i in range(30):
            self.__threads[i].start()

    def finishedThread(self, bestAnt):
        self.__count += 1
        self.__fitnesses.append(bestAnt.fitness())
        print("new thread finished", self.__count)
        if self.__count == 30:
            self.poolFinishedSignal.emit(self.__fitnesses)
