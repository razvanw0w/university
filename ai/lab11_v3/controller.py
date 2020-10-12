from random import random, choice

from lab11_v3.chromosome import Chromosome, classes


class Population:
    def __init__(self, trainingData, output, numberOfIndividuals = 100):
        self.trainingData = trainingData
        self.output = output
        self.population = [Chromosome() for _ in range(numberOfIndividuals)]
        self.numberOfIndividuals = numberOfIndividuals
        for chromosome in self.population:
            chromosome.build()

    def train(self):
        new = []
        for i in range(self.numberOfIndividuals):
            if random() < 0.5:
                new.append(Chromosome.mutate(choice(self.population)))
            else:
                new.append(Chromosome.crossover(choice(self.population), choice(self.population)))
        self.population += new


        for chromosome in self.population:
            chromosome.getFitness(self.trainingData, self.output)


        fitnesses = [(chromosome, chromosome.fitness) for chromosome in self.population]
        fitnesses = sorted(fitnesses, key=lambda x: x[1])
        self.population = [x[0] for x in fitnesses[:self.numberOfIndividuals]]
        return fitnesses[0][1] / len(self.trainingData)



    def predict(self, input):
        fitnesses = [(chromosome, chromosome.fitness) for chromosome in self.population]
        fitnesses = sorted(fitnesses, key=lambda x: x[1])
        best = fitnesses[0][0]
        output = int(round(best.evaluate(0, input)[0]))
        if output > 3:
            return 'Inexistent class'
        return classes[output]
