import random

class Repository:
    def __init__(self, fileName):
        self.fileName = fileName

    def getScaleRecordsFromFile(self):
        records = []
        f = open(self.fileName, "r")
        line = f.readline().strip()
        while line != "":
            record = line.split(",")
            record[1] = int(record[1])
            record[2] = int(record[2])
            record[3] = int(record[3])
            record[4] = int(record[4])
            records.append(record)
            line = f.readline().strip()
        f.close()
        return records

    def getTrainAndTestData(self, trainDataPercent):
        records = self.getScaleRecordsFromFile()
        indices = list(range(len(records)))
        random.shuffle(indices)
        trainDataRecordsNumber = int(trainDataPercent * len(records))

        trainData = []
        testData = []
        for i in range(trainDataRecordsNumber):
            trainData.append(records[indices[i]])
        for i in range(trainDataRecordsNumber, len(records)):
            records[indices[i]][0] = ''
            testData.append(records[indices[i]])
        return trainData, testData