import csv

def fetchTrainData():
    input = []
    output = []
    with open('sensor_readings_24.data') as f:
        for row in csv.reader(f, delimiter = ','):
            input.append([float(row[i]) for i in range(24)])
            output.append(row[24])
    return input, output

def fetchTestData():
    input = []
    output = []
    with open('test.in') as f:
        for row in csv.reader(f, delimiter=','):
            input.append([float(row[i]) for i in range(24)])
            output.append(row[24])
    return input