class UI:
    def __init__(self, controller):
        self.controller = controller

    def run(self):
        choice = ""
        while choice != "exit":
            choice = input(">")
            pieces = choice.strip().split()
            if pieces[0] == "train":
                epochs = int(pieces[1])
                self.controller.trainModel(epochs)
                print("Done training for", epochs, "epochs")
            elif pieces[0] == "test":
                results = self.controller.testModel()
                print("Test loss:", results[0], "Test accuracy:", results[1] * 100)
            elif pieces[0] == "feed":
                file = pieces[1]
                output = self.controller.feed(file)
                print("File:", file, "Prediction:", output)