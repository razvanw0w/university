from lab6.ui import UI
from lab6.controller import Controller
from lab6.repository import Repository


if __name__ == "__main__":
    # bestAcc = 0
    # for i in range(10000):
    #     acc = runDT()
    #     bestAcc = max(bestAcc, acc)
    #     print(i, 'Accuracy:', str(acc) + '%')
    # print('Best accuracy:', str(bestAcc) + '%')
    repository = Repository("scale.data")
    controller = Controller(repository)
    ui = UI(controller)
    ui.run()
