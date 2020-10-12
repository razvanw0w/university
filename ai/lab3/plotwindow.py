import matplotlib.pyplot as plt
import numpy as np
from PyQt5.QtWidgets import QDialog, QVBoxLayout, QLabel
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar


class PlotWindow(QDialog):
    def __init__(self, fitnesses):
        super(PlotWindow, self).__init__()

        print("population set has", len(fitnesses))

        # a figure instance to plot on
        self.figure = plt.figure()

        # this is the Canvas Widget that displays the `figure`
        # it takes the `figure` instance as a parameter to __init__
        self.canvas = FigureCanvas(self.figure)

        # this is the Navigation widget
        # it takes the Canvas widget and a parent
        self.toolbar = NavigationToolbar(self.canvas, self)

        self.label = QLabel(self)

        # set the layout
        layout = QVBoxLayout()
        layout.addWidget(self.toolbar)
        layout.addWidget(self.canvas)
        layout.addWidget(self.label)
        self.setLayout(layout)

        mean = np.mean(fitnesses)
        dev = np.std(fitnesses)
        self.label.setText("mean = " + str(mean) + " std dev = " + str(dev))
        self.figure.clear()
        ax = self.figure.add_subplot(111)
        ax.hist(fitnesses)
        self.canvas.draw()
