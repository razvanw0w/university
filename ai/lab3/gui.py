from PyQt5 import QtCore, QtWidgets
from PyQt5.QtCore import pyqtSignal

from lab3.ea import EA
from lab3.gui_interface import Ui_Form
from lab3.hc import HC
from lab3.plotwindow import PlotWindow
from lab3.pso import PSO
from lab3.validationpool import ValidationPool


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
        self.validateEAButton.clicked.connect(self.validateEASlot)
        self.validatePSOButton.clicked.connect(self.validatePSOSlot)

    def __hcRun(self):
        n = int(self.nLineEdit.text())
        s = [int(x) for x in self.sLineEdit.text().strip().split()]
        t = [int(x) for x in self.tLineEdit.text().strip().split()]
        iterations = int(self.iterationsLineEdit.text())
        self.solutionTextEdit.setText("")
        self.__activeThread = HC(iterations, n, s, t)
        self.solutionTextEdit.setText("hc thread started")
        self.__activeThread.finishedSignal.connect(self.__hcRunFinished)
        self.__activeThread.bestSolutionSignal.connect(self.__hcBestSolutionFinished)
        self.__activeThread.currentIterationSignal.connect(self.__hcCurrentIterationFinished)
        self.wantsBestSolutionSignal.connect(self.__activeThread.getBestSolutionUntilNow)
        self.wantsCurrentIterationSignal.connect(self.__activeThread.getCurrentIteration)
        self.wantsStopSignal.connect(self.__activeThread.stopRun)
        self.__activeThread.start()

    def __hcValidateRun(self):
        pass

    def __hcRunFinished(self, state):
        self.solutionTextEdit.setText(str(state))
        self.solutionTextEdit.append(str(state.fitness()))

    def __hcBestSolutionFinished(self, state):
        self.solutionTextEdit.setText("best until now hc\n" + str(state))
        self.solutionTextEdit.append(str(state.fitness()))

    def __hcCurrentIterationFinished(self, iteration):
        self.lineEdit.setText(str(iteration))

    def __eaRun(self):
        n = int(self.nLineEdit.text())
        s = [int(x) for x in self.sLineEdit.text().strip().split()]
        t = [int(x) for x in self.tLineEdit.text().strip().split()]
        generations = int(self.iterationsLineEdit.text())
        mutation = float(self.mutationLineEdit.text())
        population = int(self.populationLineEdit.text())
        self.solutionTextEdit.setText("")
        self.__activeThread = EA(generations, n, s, t, mutation, population)
        self.__activeThread.finishedSignal.connect(self.__eaRunFinished)
        self.__activeThread.getPopulationSignal.connect(self.__eaBestSolutionFinished)
        self.__activeThread.currentIterationSignal.connect(self.__eaCurrentIterationFinished)
        self.wantsBestSolutionSignal.connect(self.__activeThread.getPopulationUntilNow)
        self.wantsCurrentIterationSignal.connect(self.__activeThread.getCurrentIteration)
        self.wantsStopSignal.connect(self.__activeThread.stopRun)
        self.solutionTextEdit.setText("ea thread started")
        self.__activeThread.start()

    def __eaRunFinished(self, population):
        state = max(population, key = lambda x: x.fitness())
        self.solutionTextEdit.setText(str(state))
        self.solutionTextEdit.append(str(state.fitness()))

    def __eaBestSolutionFinished(self, population):
        state = max(population, key = lambda x: x.fitness())
        self.solutionTextEdit.setText("best until now ea\n" + str(state))
        self.solutionTextEdit.append(str(state.fitness()))

    def __eaCurrentIterationFinished(self, iteration):
        self.lineEdit.setText(str(iteration))

    def __eaValidateRun(self):
        self.__validationPool = ValidationPool('EA')
        self.__validationPool.fillEAThreads()
        self.__validationPool.poolFinishedSignal.connect(self.__eaValidateRunFinished)
        self.__validationPool.start()

    def __eaValidateRunFinished(self, fitnesses):
        window = PlotWindow(fitnesses)
        window.show()

    # pso
    def __psoRun(self):
        n = int(self.nLineEdit.text())
        s = [int(x) for x in self.sLineEdit.text().strip().split()]
        t = [int(x) for x in self.tLineEdit.text().strip().split()]
        generations = int(self.iterationsLineEdit.text())
        population = int(self.populationLineEdit.text())
        inertia = float(self.inertiaLineEdit.text())
        cognitive = float(self.cognitiveLineEdit.text())
        social = float(self.socialLineEdit.text())
        nbhd = int(self.neighbourhoodLineExit.text())

        self.solutionTextEdit.setText("")
        self.__activeThread = PSO(generations, n, s, t, population, inertia, cognitive, social, nbhd)
        self.__activeThread.finishedSignal.connect(self.__psoRunFinished)
        self.__activeThread.getPopulationSignal.connect(self.__psoBestSolutionFinished)
        self.__activeThread.currentIterationSignal.connect(self.__psoCurrentIterationFinished)
        self.wantsBestSolutionSignal.connect(self.__activeThread.getPopulationUntilNow)
        self.wantsCurrentIterationSignal.connect(self.__activeThread.getCurrentIteration)
        self.wantsStopSignal.connect(self.__activeThread.stopRun)
        self.solutionTextEdit.setText("pso thread started")
        self.__activeThread.start()

    def __psoRunFinished(self, population):
        state = max(population, key=lambda x: x.getBestFitness())
        self.solutionTextEdit.setText(state.getBestMatrixString())
        self.solutionTextEdit.append(str(state.getBestFitness()))

    def __psoBestSolutionFinished(self, population):
        state = max(population, key=lambda x: x.getBestFitness())
        self.solutionTextEdit.setText("best until now pso\n" + state.getBestMatrixString())
        self.solutionTextEdit.append(str(state.getBestFitness()))

    def __psoCurrentIterationFinished(self, iteration):
        self.lineEdit.setText(str(iteration))

    def __psoValidateRun(self):
        self.__validationPool = ValidationPool('PSO')
        self.__validationPool.fillPSOThreads()
        self.__validationPool.poolFinishedSignal.connect(self.__psoValidateRunFinished)
        self.__validationPool.start()

    def __psoValidateRunFinished(self, fitnesses):
        window = PlotWindow(fitnesses)
        window.show()

    @QtCore.pyqtSlot()
    def goSlot(self):
        if self.hcRadioButton.isChecked():
            self.__hcRun()
        elif self.eaRadioButton.isChecked():
            self.__eaRun()
        elif self.psoRadioButton.isChecked():
            self.__psoRun()

    @QtCore.pyqtSlot()
    def validateEASlot(self):
        self.__validationCounter = 0
        self.__populationSet = []
        self.__validationThread = None
        self.__eaValidateRun()

    @QtCore.pyqtSlot()
    def validatePSOSlot(self):
        print("entered pso validate slot")
        self.__validationCounter = 0
        self.__populationSet = []
        self.__psoValidateRun()

    @QtCore.pyqtSlot()
    def stopSlot(self):
        self.wantsStopSignal.emit()

    @QtCore.pyqtSlot()
    def bestSolutionSlot(self):
        self.wantsBestSolutionSignal.emit()

    @QtCore.pyqtSlot()
    def currentIterationSlot(self):
        self.wantsCurrentIterationSignal.emit()
