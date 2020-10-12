class State:
    def __init__(self, state, n):
        self.__values = state[:]
        self.__n = n

    def getValues(self):
        return self.__values[:]

    def setValues(self, values):
        self.__values = values[:]

    def getLength(self):
        return len(self.__values)

    def addCell(self, cell):
        self.__values.append(cell)

    @staticmethod
    def getInitialState():
        return []

    def isSolution(self):
        n = len(self.__values)
        for i in range(n):
            cell_i = self.__values[i]
            for j in range(n):
                cell_j = self.__values[j]
                if i != j:
                    if cell_i[0] == cell_j[0]:
                        return False
                    if cell_i[1] == cell_j[1]:
                        return False
                    if abs(cell_i[0] - cell_j[0]) == abs(cell_i[1] - cell_j[1]):
                        return False
        return True

    def getStateMatrix(self):
        matrix = [[0 for i in range(self.__n)] for j in range(self.__n)]
        for cell in self.__values:
            matrix[cell[0]][cell[1]] = 1
        return matrix

    def __eq__(self, otherState):
        return self.__values == otherState.getValues()
