# problem: f(x1, x2, x3, x4, x5) = ax1 + bx2 + cx3 + dx4 + ex5 + f
# find (a, b, c, d, e, f) accordingly

def computeSimpleError(entry, coefficients):
    return abs(entry[-1] - getFunctionValue(entry, coefficients))


def computeErrorFunction(coefficients, points):
    totalError = 0
    for entry in points:
        totalError += computeSimpleError(entry, coefficients) ** 2
    return totalError / float(len(points))


def getFunctionValue(entry, coefficients):
    value = 0
    for i in range(5):
        value += entry[i] * coefficients[i]
    value += coefficients[5]
    return value


def improveCoefficients(coefficients, points, learningRate):
    gradients = [0 for i in range(6)]
    n = float(len(points))
    for entry in points:
        y = entry[-1]
        x = entry[:5]
        value = getFunctionValue(entry, coefficients)
        for i in range(5):
            gradients[i] += -(2 / n) * x[i] * (y - value)
        gradients[5] += -(2 / n) * (y - value)
    return [coefficients[i] - (learningRate * gradients[i]) for i in range(6)]


def getBestCoefficients(points, coefficients, learningRate, numberOfIterations):
    for i in range(numberOfIterations):
        coefficients = improveCoefficients(coefficients, points, learningRate)
    return coefficients