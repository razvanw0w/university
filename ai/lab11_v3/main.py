from lab11_v3.controller import Population
from lab11_v3.repository import *
import pickle

epsilon = 0.6
serialized = True

if __name__ == '__main__':
    (train, output) = fetchTrainData()
    population = None
    if serialized:
        population = pickle.load(open('population.bin', 'rb'))
    else:
        population = Population(train, output)
        i = 1
        while True:
            error = population.train()
            print(error)
            i += 1
            if error < epsilon:
                break
        pickle.dump(population, open('population.bin', 'wb'))

    test = fetchTestData()
    finalOutput = []
    for i in range(len(test)):
        output = population.predict(test[i])
        print(output)
        finalOutput.append(output)
    #writeOutput('\n'.join(finalOutput))