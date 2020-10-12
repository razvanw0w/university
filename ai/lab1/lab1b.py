import matplotlib.pyplot as plt
from numpy import random


def generateBinomial(x, y):
    values = ([x] * 1000) + random.binomial(y - x, 0.5, 1000)
    return values


def generateUniform(x, y):
    values = random.uniform(low=x, high=y, size=1000)
    return values


def generateNormal(x, y):
    mean = (y - x) / 2
    stdev = (mean - x) / 3
    return random.normal(mean, stdev, 1000)


def printOptions():
    print("1. Binomial")
    print("2. Uniform")
    print("3. Standard normal")
    print("4. Exit")


def getInterval(f):
    x, y = [int(x) for x in input("interval: ").strip().split()]
    return x, y


cmds = {1: generateBinomial, 2: generateUniform, 3: generateNormal}
choice = 0
while choice != 4:
    printOptions()
    choice = int(input("Choose: "))
    if choice in range(1, 4):
        x, y = getInterval(cmds[choice])
        values = cmds[choice](x, y)
        plt.hist(values)
        plt.show()