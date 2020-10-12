from keras import datasets
from keras.utils import to_categorical
import numpy as np

class Repository:
    def __init__(self):
        self.loadData()
        self.originalInputShape = (28, 28, 1)

    def fetchDataset(self):
        (self.trainImages, self.trainLabels), (self.testImages, self.testLabels) = datasets.mnist.load_data()
        print(type(self.trainImages))

    def reshapeDataset(self):
        # keras api complies with 4D numpy arrays, that's why reshaping is needed
        trainLength = self.trainImages.shape[0]
        testLength = self.testImages.shape[0]
        self.trainImages = self.trainImages.reshape(trainLength, 28, 28, 1)
        self.testImages = self.testImages.reshape(testLength, 28, 28, 1)

        # initially had error ValueError: Error when checking target: expected dense_2 to have shape (10,) but got array with shape (1,)
        # added to transform the array of labels to binary 2d array
        self.trainLabels = to_categorical(self.trainLabels, 10)
        self.testLabels = to_categorical(self.testLabels, 10)

    def normalizeDataset(self):
        self.trainImages.astype('float32')
        self.testImages.astype('float32')

        # images represent RGB gray tones (i.e. values from 0 to 255)
        # normalizing to values from 0 to 1
        self.trainImages = self.trainImages / 255
        self.testImages = self.testImages / 255

    def loadData(self):
        self.fetchDataset()
        self.reshapeDataset()
        self.normalizeDataset()

    def getTrainData(self):
        return (self.trainImages, self.trainLabels)

    def getTestData(self):
        return (self.testImages, self.testLabels)

    def getInputShape(self):
        return self.originalInputShape