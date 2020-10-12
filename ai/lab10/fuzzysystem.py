from lab10.logger import Logger

class FuzzySystem:
    def __init__(self):
        self.inputDescriptions = {}
        self.outputDescription = None
        self.rules = []

    def addRule(self, rule):
        self.rules.append(rule)

    def addDescription(self, name, description, out = False):
        if out:
            if self.outputDescription is None:
                self.outputDescription = description
            else:
                raise ValueError('System already has an output')
        else:
            self.inputDescriptions[name] = description

    def compute(self, inputs):
        fuzzyValues = self._computeDescriptions(inputs)
        ruleValues = self._computeRulesFuzzy(fuzzyValues)
        Logger.log('fuzzy values', str(fuzzyValues))
        Logger.log('rule values', str(ruleValues))

        fuzzyOutVariables = [(list(var[0].values())[0], var[1]) for var in ruleValues]
        output = {out: 0 for out in set([var[0] for var in fuzzyOutVariables])}
        for var in fuzzyOutVariables:
            label = var[0]
            probability = var[1]
            output[label] = max(output[label], probability)
        centroidRecords = [(self.outputDescription.getPeak(outVariable), probability) for (outVariable, probability) in output.items()]
        Logger.log('centroid records', str(centroidRecords))
        centroid = sum([out * probability for (out, probability) in centroidRecords]) / sum(probability for (out, probability) in centroidRecords)
        return centroid

    def _computeDescriptions(self, inputs):
        return {variableName: self.inputDescriptions[variableName].fuzzify(val) for variableName, val in inputs.items()}

    def _computeRulesFuzzy(self, fuzzyValues):
        ruleValues = []
        Logger.log('compute rule values for fuzzy values', str(fuzzyValues))
        for rule in self.rules:
            result = rule.evaluate(fuzzyValues)
            ruleValues.append(result)
        return ruleValues
