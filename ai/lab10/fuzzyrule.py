from lab10.logger import Logger

class FuzzyRule:
    def __init__(self, inputs, out):
        self.outputVariable = out
        self.inputs = inputs

    def evaluate(self, inputs):
        Logger.log('list of input values for input ' + str(self.inputs), str([inputs[descriptionName][variableName] for descriptionName, variableName in self.inputs.items()]))
        return [self.outputVariable, min([inputs[descriptionName][variableName] for descriptionName, variableName in self.inputs.items()])]

    def __str__(self):
        return str(self.inputs) + " " + str(self.outputVariable)