from keras.models import Sequential
from keras.layers import Conv2D
from keras.layers import MaxPooling2D
from keras.layers import Flatten
from keras.layers import Dense
from keras.layers import Dropout
from keras import optimizers
from keras.models import save_model
from keras.models import load_model
import numpy as np
import matplotlib.image as mpimg
from matplotlib import pyplot as plt

# trials
# 1 epoch
# Adam, CategoricalCrossEntropy => 97.35%
# Adadelta, CategoricalCrossEntropy => 97.75%
# Nadam, CategoricalCrossEntropy => 97.51%
# 3 epochs
# Adam, CategoricalCrossEntropy => 98.29%
# Adadelta, CategoricalCrossEntropy => 98.40%
# Nadam, CategoricalCrossEntropy => 98.22%
# Adadelta, 5x5 Conv filter, CategoricalCrossEntropy => 98.61%
class Controller:
    def __init__(self, repo, load = False):
        self.repo = repo
        self.inputShape = repo.getInputShape()
        self.load = load
        self.createModel()


    def loadModel(self):
        if self.load:
            self.model = load_model("models/model")
        else:
            self.buildModel()
            self.compileModel()

    def saveModel(self):
        self.model.save("models/model")

    def createModel(self):
        self.loadModel()

    def buildModel(self):
        self.model = Sequential()
        # convolution layer
        self.model.add(Conv2D(28, kernel_size=(3, 3), input_shape=self.inputShape))
        # max pool layer
        self.model.add(MaxPooling2D(pool_size=(2, 2)))
        # flattening layer, preparation for regular column layer
        self.model.add(Flatten())
        # densely-connected layer activated with linear function
        self.model.add(Dense(128, activation='relu'))
        # dropout layer (randomly set input units to 0 with a specified frequency (e.g. 0.2) - prevent overfitting
        self.model.add(Dropout(0.1))
        # densely-connected layer with softmax activation (transform the whole thing in probabilities for digits from 0 to 9
        self.model.add(Dense(10, activation='softmax'))

    def compileModel(self):
        optimizer = optimizers.Adam(learning_rate=0.0002)
        self.model.compile(optimizer=optimizer, loss='categorical_crossentropy', metrics=['accuracy'])

    def trainModel(self, epochs):
        trainImages, trainLabels = self.repo.getTrainData()
        self.model.fit(x=trainImages, y=trainLabels, epochs=epochs)
        self.saveModel()

    def testModel(self):
        testImages, testLabels = self.repo.getTestData()
        plt.imshow(testImages[0].reshape(28, 28), cmap='Greys')
        plt.show()
        return self.model.evaluate(testImages, testLabels)

    def rgb2gray(self, image):
        new = np.dot(image[...,:3], [0.2989, 0.5870, 0.1140])
        for i in range(28):
            for j in range(28):
                new[i][j] = 1 - new[i][j]
        return new

    def feed(self, file):
        image = mpimg.imread(file)
        grayImage = self.rgb2gray(image)
        plt.imshow(grayImage, cmap='Greys')
        plt.show()
        prediction = self.model.predict(grayImage.reshape(1, 28, 28, 1))
        return prediction.argmax()