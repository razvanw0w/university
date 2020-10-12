from lab10.logger import Logger

class FuzzyDescription:
    def __init__(self):
        self.regions = {}
        self.peaks = {}

    def addRegion(self, variableName, memberFunction, peak):
        self.regions[variableName] = memberFunction
        self.peaks[variableName] = peak

    def fuzzify(self, value):
        fuzzifyDict = {}
        for name, memberFunction in self.regions.items():
            fuzzifyDict[name] = memberFunction(value)
        return fuzzifyDict

    def getPeak(self, variableName):
        return self.peaks[variableName]

    # def defuzzify(self, variableName, value):
    #     Logger.log('defuzzify', "")
    #     Logger.log('compute inverse', str(variableName) + " " + str(value) + " " + str(self.inverse[variableName](value)))
    #     return self.inverse[variableName](value)

    def __str__(self):
        return str(self.regions) + " " + str(self.peaks)