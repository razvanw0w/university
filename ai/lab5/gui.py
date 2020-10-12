from PyQt5 import QtCore, QtWidgets
from PyQt5.QtCore import pyqtSignal

from lab5.aco import ACO
from lab5.gui_interface import Ui_Form
from lab5.plotwindow import PlotWindow
from lab5.problem import Problem
from lab5.validationpool import ValidationPool


class GUI(QtWidgets.QWidget, Ui_Form):
    wantsBestSolutionSignal = pyqtSignal()
    wantsCurrentIterationSignal = pyqtSignal()
    wantsStopSignal = pyqtSignal()

    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.__activeThread = None
        self.__validationPool = None
        self.__populationSet = []

    def setupUi(self, form):
        super().setupUi(form)
        self.goButton.clicked.connect(self.goSlot)
        self.stopButton.clicked.connect(self.stopSlot)
        self.bestSolutionButton.clicked.connect(self.bestSolutionSlot)
        self.currentIterationButton.clicked.connect(self.currentIterationSlot)
        self.validateButton.clicked.connect(self.validateSlot)

    @QtCore.pyqtSlot()
    def goSlot(self):
        n = int(self.nLineEdit.text())
        s = [int(x) for x in self.sLineEdit.text().strip().split()]
        t = [int(x) for x in self.tLineEdit.text().strip().split()]
        problem = Problem(n, s, t)
        epochs = int(self.epochsLineEdit.text())
        population = int(self.populationLineEdit.text())
        alpha = float(self.alphaLineEdit.text())
        beta = float(self.betaLineEdit.text())
        rho = float(self.rhoLineEdit.text())
        q0 = float(self.probabilityLineEdit.text())
        self.solutionTextEdit.setText("")
        self.__activeThread = ACO(problem, epochs, population, alpha, beta, rho, q0)
        self.__activeThread.finishedSignal.connect(self.__runFinished)
        self.__activeThread.bestSolutionSignal.connect(self.__bestSolutionFinished)
        self.__activeThread.currentIterationSignal.connect(self.__currentEpochFinished)
        self.wantsStopSignal.connect(self.__activeThread.stopRun)
        self.wantsBestSolutionSignal.connect(self.__activeThread.getBestSolutionUntilNow)
        self.wantsCurrentIterationSignal.connect(self.__activeThread.getCurrentIteration)
        self.solutionTextEdit.setText("aco thread started")
        self.__activeThread.start()

    def __runFinished(self, state):
        if state is None:
            self.solutionTextEdit.setText("No best solution found (first epoch didnt finish)\n")
        else:
            self.solutionTextEdit.setText(str(state))
            self.solutionTextEdit.append(str(state.fitness()))

    def __bestSolutionFinished(self, state):
        if state is None:
            self.solutionTextEdit.setText("No best solution found (first epoch didnt finish)\n")
        else:
            self.solutionTextEdit.setText("best until now aco \n" + str(state))
            self.solutionTextEdit.append(str(state.fitness()))

    def __currentEpochFinished(self, epoch):
        self.currentEpochLineEdit.setText(str(epoch))

    def __psoValidate(self):
        self.__validationPool = ValidationPool()
        self.__validationPool.fillACOThreads()
        self.__validationPool.poolFinishedSignal.connect(self.__psoValidateFinished)
        self.__validationPool.start()

    def __psoValidateFinished(self, fitnesses):
        window = PlotWindow(fitnesses)
        window.show()

    @QtCore.pyqtSlot()
    def validateSlot(self):
        self.__psoValidate()

    @QtCore.pyqtSlot()
    def stopSlot(self):
        self.wantsStopSignal.emit()

    @QtCore.pyqtSlot()
    def bestSolutionSlot(self):
        self.wantsBestSolutionSignal.emit()

    @QtCore.pyqtSlot()
    def currentIterationSlot(self):
        self.wantsCurrentIterationSignal.emit()
