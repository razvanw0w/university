import numpy as np
import matplotlib as mpl

def linear(x):
    return x

def linear_derivative(x) :
    return 1

class NeuralNetwork:
    def __init__(self, hiddenLayerNeuronCount):
        self.weights1 = np.random.rand(5, hiddenLayerNeuronCount)
        self.weights2 = np.random.rand(hiddenLayerNeuronCount, 1)
        self.output = np.zeros(1)
        self.loss = []
        self.maxLoss = -10000000000

    def feedForward(self, input):
        self.npInput = np.array([input[:5]])
        self.realOutput = np.array([[input[5]]])
        # (1, 5) * (5, x) = (1, x)
        self.layer1 = linear(np.dot(self.npInput, self.weights1))
        # (1, x) * (x, 1) = (1, 1)
        self.output = linear(np.dot(self.layer1, self.weights2))
        return self.output

    def backPropagate(self, learningRate, quotient):
        d_weights2 = np.dot(np.transpose(self.layer1), (2 * (self.realOutput - self.output) * linear_derivative(self.output)))
        d_weights1 = np.dot(np.transpose(self.npInput), (np.dot(2 * (self.realOutput - self.output) * linear_derivative(self.output), np.transpose(self.weights2)) * linear_derivative(self.layer1)))

        self.weights1 += learningRate * d_weights1
        self.weights2 += learningRate * d_weights2
        currentLoss = sum((self.realOutput - self.output)**2)
        #print(currentLoss)
        self.maxLoss = max(self.maxLoss, currentLoss)

    def trainInputs(self, inputs):
        n = len(inputs)
        self.maxLoss = -10000000000
        for input in inputs:
            self.feedForward(input)
            self.backPropagate(0.00000001, n)
        print(self.maxLoss)
        self.loss.append(self.maxLoss)
