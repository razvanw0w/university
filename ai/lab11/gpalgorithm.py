from random import shuffle

from lab11.chromosome import Chromosome
from lab11.population import Population
from lab11.classifier import Classifier
from numpy import random

HEADER = []


class Controller:
    def __init__(self, trainingFilename, inputFilename, outputFilename):
        self.n = 0
        self.input = []
        self.output = []
        self.inputTesting = []
        self.outputTesting = []
        self.inputTraining = []
        self.outputTraining = []
        self.trainingFilename = trainingFilename
        self.inputFilename = inputFilename
        self.outputFilename = outputFilename

    def run(self, nrOfIndividuals, iterations, trainingSize, testingSize, mutationProbability, crossoverProbability,
            epsilon):
        self.nrOfIndividuals = nrOfIndividuals
        self.trainingSize = trainingSize
        self.testingSize = testingSize
        self.iterations = iterations
        self.population = Population(self.nrOfIndividuals)
        self.mutationProbability = mutationProbability
        self.crossoverProbability = crossoverProbability
        self.epsilon = epsilon
        self.loadData()
        self.start()

    def start(self):
        accuracy = -1.0
        while accuracy < self.epsilon:
            self.population.evaluate(self.inputTraining, self.outputTraining)

            for index in range(self.iterations):
                print("Iteration: " + str(index))
                self.iteration(index)
                self.population.evaluate(self.inputTraining, self.outputTraining)
                self.population.selection(self.nrOfIndividuals)
            best = self.population.best(1)[0]
            count = 0
            print("Training accurracy", best.fitness, "%")
            for index in range(len(self.inputTesting)):
                if best.fitness == 100:
                    print(str(Classifier.classify(best.predict(self.inputTesting[index]))) + " == " + str(
                        self.outputTesting[index]))
                if Classifier.classify(best.predict(self.inputTesting[index])) == self.outputTesting[index]:
                    count += 1
            accuracy = float(count / len(self.inputTesting) * 100)
            print("Current accuracy: ", accuracy, "%")

        print("Best: " + str(best.root))
        print("Correct guesses ", count)
        print("That is ", accuracy, "% accuracy")
        with open(self.outputFilename, "w") as f:
            f.write("Correct guesses " + str(count))
            f.write("\nThat is " + str(accuracy) + "%")

    def loadData(self):
        global HEADER
        with open(self.trainingFilename, "r") as f:
            HEADER = f.readline().split(',')[:-1]
            inputLines = f.readlines()
            shuffle(inputLines)
            for line in inputLines[:self.trainingSize]:
                values = list(line.strip("\n").split(","))
                mapvalues = list(map(float, values[:-1]))
                self.inputTraining.append(mapvalues[:])
                self.outputTraining.append(values[-1])
                self.n += 1

        with open(self.inputFilename, "r") as f:
            inputLines = f.readlines()
            shuffle(inputLines)
            for line in inputLines[:self.testingSize]:
                values = list(line.strip("\n").split(","))
                mapvalues = list(map(float, values[:-1]))
                self.inputTesting.append(mapvalues[:])
                self.outputTesting.append(values[-1])

        pair = list(zip(self.inputTesting, self.outputTesting))
        shuffle(pair)
        self.inputTesting, self.outputTesting = zip(*pair)

    def iteration(self, i):
        offspring = Population(self.nrOfIndividuals)
        for child in range(self.nrOfIndividuals):
            first_pick = random.randint(0, self.nrOfIndividuals)
            second_pick = first_pick
            while second_pick == first_pick:
                second_pick = random.randint(0, self.nrOfIndividuals)
            offspring.individuals[child] = Chromosome.crossover(self.population.individuals[first_pick],
                                                                self.population.individuals[second_pick],
                                                                self.crossoverProbability)
            offspring.individuals[child].mutate(self.mutationProbability)
        offspring.evaluate(self.inputTraining, self.outputTraining)
        self.population.reunion(offspring)
        self.population.selection(self.nrOfIndividuals)