from copy import deepcopy

from itertools import permutations


class Problem:
    def __init__(self, n, s, t):
        self.n = n
        self.s = deepcopy(s)
        self.t = deepcopy(t)
        self.permutationSet = list(permutations(list(range(self.n))))
