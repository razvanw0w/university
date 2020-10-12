from lab11_v2.Chromosome import Chromosome

class Population:
    def __init__(self, nrOfIndividuals):
        self.nrOfIndividuals = nrOfIndividuals
        self.individuals = [Chromosome() for _ in range(nrOfIndividuals)]

    def evaluate(self, inputTraining, outputTraining):
        for chromosome in self.individuals:
            chromosome.evaluate(inputTraining, outputTraining)

    def selection(self, nrOfIndividuals):
        #select only the n(nrOfIndividuals) best chromosomes 
        if nrOfIndividuals < self.nrOfIndividuals:
            self.nrOfIndividuals = nrOfIndividuals
            self.individuals = sorted(self.individuals, key=lambda x: x.fitness,reverse=True)
            self.individuals = self.individuals[:nrOfIndividuals]

    def best(self, maxIndividuals):
        #take only the best m(maxIndviduals) chromosomes
        self.individuals = sorted(self.individuals, key=lambda x: x.fitness,reverse=True)
        return self.individuals[:maxIndividuals]

    def reunion(self, offsprings):
        #combine 
        self.nrOfIndividuals += offsprings.nrOfIndividuals
        self.individuals = self.individuals + offsprings.individuals