from lab2.controller import Controller
from lab2.problem import Problem

class UI:
    def __init__(self):
        self.__controller = None
        self.__problem = None

    def mainMenu(self):
        while True:
            n = int(input("How much is the board's size? (= the number of queens): "))
            problem = Problem(n)
            self.__controller = Controller(problem)
            self.__problem = problem

            print("1. DFS")
            print("2. Greedy")
            choice = int(input("Choice?: "))
            if choice == 1:
                self.__goDFS()
            elif choice == 2:
                self.__goGreedy()

    def __goDFS(self):
        outcome = self.__controller.dfs()
        if outcome is None:
            print("No solution found by DFS")
        else:
            for solution in outcome:
                self.__printMatrix(solution.getStateMatrix())

    def __printMatrix(self, matrix):
        for line in matrix:
            for item in line:
                print(item, end = ' ')
            print()
        print()

    def __goGreedy(self):
        outcome = self.__controller.greedy()
        if outcome is None:
            print("No solution found by greedy")
        else:
            self.__printMatrix(outcome.getStateMatrix())
