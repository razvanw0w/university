import matplotlib.pyplot as plt

class UI:
    def __init__(self, controller):
        self.controller = controller

    def run(self):
        choice = ""
        while choice != "exit":
            choice = input(">")
            pieces = choice.strip().split()
            if pieces[0] == "train":
                iterations = int(pieces[1])
                loss = self.controller.train(iterations)
                print("Done training for", iterations, "iterations")
                iterations = list(range(1, len(loss) + 1))
                print(iterations)
                print(loss)
                plt.plot(iterations, loss, label = 'loss over number of iterations')
                plt.xlabel('iterations')
                plt.ylabel('loss function')
                plt.legend()
                plt.show()
            elif pieces[0] == "test":
                results = self.controller.test()
                for result in results:
                    print("Point: {} Real value: {} Computed value: {} Error: {}".format(result[0], result[1], result[2], result[3]))
