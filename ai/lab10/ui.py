class UI:
    def __init__(self, ctrl, inputFile, outputFile):
        self.ctrl = ctrl
        self.inputFile = inputFile
        self.outputFile = outputFile

    def _writeAnswers(self, answers):
        f = open(self.outputFile, "w")
        for val in answers:
            f.write(str(val) + '\n')
        f.close()

    def _readInputs(self):
        f = open(self.inputFile, "r")
        inputs = []
        while True:
            line = f.readline().strip()
            if line == "":
                break
            parts = line.split()
            n = len(parts)
            input = {}
            for i in range(0, n, 2):
                label = parts[i]
                val = int(parts[i + 1])
                input[label] = val
            inputs.append(input)
        f.close()
        return inputs

    def _solve(self, inputs):
        answers = []
        for input in inputs:
            output = self.ctrl.compute(input)
            answers.append(output)
        return answers


    def run(self):
        inputs = self._readInputs()
        answers = self._solve(inputs)
        self._writeAnswers(answers)