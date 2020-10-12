class PermutationUtils:
    @staticmethod
    def distance(perm1, perm2):
        n = len(perm1)
        count = 0
        for i in range(n):
            if perm1[i] == perm2[i]:
                count += 1
        if count > 0:
            return count
        return 0.5

    @staticmethod
    def getPermutationIndex(perm):
        index = 0
        position = 2
        factor = 1
        n = len(perm)
        for p in range(n - 2, -1, -1):
            successors = 0
            for q in range(p + 1, n):
                if perm[p] > perm[q]:
                    successors += 1
            index += (successors * factor)
            factor *= position
            position += 1
        return index
