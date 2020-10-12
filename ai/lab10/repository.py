from lab10.fuzzysystem import FuzzySystem
from lab10.fuzzyrule import FuzzyRule
from lab10.fuzzydescription import FuzzyDescription
from lab10.utils import Utils
from lab10.logger import Logger


class Repository:
    def  __init__(self):
        self.system = FuzzySystem()

    def loadRules(self, rulesFileName):
        f = open(rulesFileName, "r")
        while True:
            line = f.readline().strip()
            if line == "":
                break
            parts = line.split()
            n = len(parts)
            inputDict = {}
            outputDict = {}
            for i in range(0, n - 2, 2):
                label = parts[i]
                val = parts[i + 1]
                inputDict[label] = val
            outputDict[parts[-2]] = parts[-1]
            self.system.addRule(FuzzyRule(inputDict, outputDict))
        f.close()

    def _getFunction(self, parts):
        type = parts[0]
        if type == 'tri':
            return Utils.triangularRegion(int(parts[1]), int(parts[2]), int(parts[3]))
        elif type == 'trap':
            return Utils.trapezoidalRegion(int(parts[1]), int(parts[2]), int(parts[3]), int(parts[4]))

    def _getPeak(self, parts):
        return int(parts[2])

    def _getInverse(self, parts):
        type = parts[0]
        if type == 'iline':
            return Utils.inverseLine(int(parts[1]), int(parts[2]))
        elif type == 'itri':
            return Utils.inverseTriangular(int(parts[1]), int(parts[2]), int(parts[3]))

    def loadDescriptions(self, descriptionsFileName):
        f = open(descriptionsFileName, "r")
        while True:
            line = f.readline().strip()
            if line == "":
                break
            parts = line.split()
            out = False
            if len(parts) == 3:
                out = True
            descriptionName = parts[0]
            description = FuzzyDescription()
            n = int(parts[1])
            for i in range(n):
                regionLine = f.readline().strip()
                region = regionLine.split()
                label = region[0]
                function = self._getFunction(region[1:])
                peak = self._getPeak(region[1:])
                description.addRegion(label, function, peak)
            self.system.addDescription(descriptionName, description, out)
        f.close()

    def getSystem(self):
        return self.system