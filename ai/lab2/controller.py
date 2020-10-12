from lab2.state import State

class Controller:
    def __init__(self, problem):
        self.__problem = problem

    def orderStates(self, statesList):
        return sorted(statesList, key=lambda x: self.__problem.heuristic(x), reverse=True)

    def __dfsHelper(self, state, solutionList):
        if state.getLength() == self.__problem.n:
            if state.isSolution() and state not in solutionList:
                solutionList.append(state)
        else:
            children = self.__problem.expand(state)
            for child in children:
                self.__dfsHelper(child, solutionList)

    def dfs(self):
        state = State([], self.__problem.n)
        solutionList = []
        self.__dfsHelper(state, solutionList)
        if len(solutionList) == 0:
            return None
        return solutionList

    def greedy(self):
        state = State([], self.__problem.n)
        done = False
        while not done:
            children = self.__problem.expand(state)
            state = self.orderStates(children)[0]
            if state.getLength() == self.__problem.n:
                done = True
        if state.isSolution():
            return state
        return None
