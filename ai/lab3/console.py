from lab3.hc import HC


class Console:
    def __init__(self):
        self.__commands = {"hc": self.__runHC}

    def __printMatrix(self, matrix):
        for line in matrix:
            for item in line:
                print(item, end=' ')
            print()

    def __runHC(self, n, s, t):
        runs = int(input("number of trials = "))
        hc = HC(runs, n, s, t)
        state = hc.run()
        self.__printMatrix(state.getMatrix())
        print(state.fitness())

    def run(self):
        while True:
            n = int(input("n = "))
            s = [int(x) for x in input("s = ").strip().split()]
            t = [int(x) for x in input("t = ").strip().split()]
            # technique = input("technique (hc, ea) = ")
            self.__commands["hc"](n, s, t)
