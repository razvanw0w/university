import random
from copy import deepcopy


class Repository:
    def __init__(self, fileName):
        self.fileName = fileName
        self.train = []
        self.test = []
        self.entries = []
        self.loadData()

    def loadData(self):
        f = open(self.fileName, "r")
        lines = f.readlines()
        for line in lines:
            if line.strip():
                entry = [float(x) for x in line.strip().split()]
                self.entries.append(entry)
        f.close()

    def fetchEntries(self):
        return self.entries[:]

    def getTrainData(self):
        return deepcopy(self.train)
