import sys

from PyQt5 import QtWidgets

from lab3.gui import GUI

app = QtWidgets.QApplication(sys.argv)
window = GUI()
window.show()
sys.exit(app.exec_())
