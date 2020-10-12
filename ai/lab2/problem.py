from lab2.state import State

class Problem:
    def __init__(self, n):
        self.n = n

    def expand(self, state):
        stateListSize = state.getLength()
        stateList = state.getValues()
        i = None
        j = None
        if stateListSize == 0:
            i = 0
            j = 0
        else:
            lastCell = stateList[-1]
            i = lastCell[0]
            j = lastCell[1] + 1
        allStates = []
        while i < self.n:
            while j < self.n:
                oldState = State(stateList, self.n)
                oldState.addCell((i, j))
                allStates.append(oldState)
                j += 1
            i += 1
            j = 0
        return allStates[:]

    def heuristic(self, state):
        score = 0
        stateList = state.getValues()
        n = len(stateList)
        #print(stateList, end = ' ')
        for i in range(n):
            cell_i = stateList[i]
            for j in range(n):
                cell_j = stateList[j]
                if i != j:
                    if cell_i[0] == cell_j[0]:
                        score -= 1000
                    if cell_i[1] == cell_j[1]:
                        score -= 1000
                    if abs(cell_i[0] - cell_j[0]) == abs(cell_i[1] - cell_j[1]):
                        score -= 1000

        lastCell = stateList[-1]
        i = lastCell[0] + 1
        j = 1

        while i < self.n:
            while j < self.n:
                for cell in stateList:
                    x = cell[0]
                    y = cell[1]
                    if x != i:
                        score += 1
                    if y != i:
                        score += 1
                    if abs(x - i) != abs(y - j):
                        score += 1
                j += 1
            i += 1
            j = 0
        #print(score)
        return score
