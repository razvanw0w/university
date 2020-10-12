from numpy import random

from numpy.random.mtrand import choice


#24 sensors values and 10 constants
T = ["value" + str(x) for x in range(24)] + \
    ["c" + str(x) for x in range(10)]
#the function choice probability
P = [0.332, 0.332, 0.332, 0.002, 0.002]
F = ['+', '-', '*', 'sin', 'cos']
C = [random.uniform(0, 1) for _ in range(10)]


class Node:
    def __init__(self):
        self.val = None
        self.left = None
        self.right = None
        self.size = 1

    def deepcopy(self):
        copy = Node()
        copy.val = self.val
        copy.size = self.size
        if self.left:
            copy.left = self.left.deepcopy()
        if self.right:
            copy.right = self.right.deepcopy()
        return copy


    def init(self, d):
        if d <= 0:
            self.val = choice(T)
            return
        self.val = choice(F, p=P)
        self.left = Node()
        self.left.init(d - 1)
        self.size += self.left.size
        #if it is a binary operation create the right tree too
        if self.val != 'sin' and self.val != 'cos':
            self.right = Node()
            self.right.init(d - 1)
            self.size += self.right.size

    def mutate(self, pos,d):
        if pos <= 0:
            return self
        if pos > self.size:
            return self
        if self.left and pos <= self.left.size:
            self.left.mutate(pos,d-1)
        else:
            leftSize = 0
            if self.left:
                leftSize = self.left.size
            if leftSize + 1 == pos:
                if self.val in T:
                    #if we are in a terminal node we have a value here so we change it
                    #with another value/constant
                    self.val = choice(T)
                else:
                    #if it is not a terminal node we change the node creating a new one
                    new_node=Node()
                    new_node.init(d-1)
                    self.left=new_node
            else:
                self.right.mutate(pos - leftSize - 1,d-1)

    def change(self, root, node1, node2):
        self.val = root.val
        if root.left:
            if root.left == node1:
                self.left = node2.deepcopy()
            else:
                self.left = Node()
                self.left.change(root.left, node1, node2)
        if root.right:
            if root.right == node1:
                self.right = node2.deepcopy()
            else:
                self.right = Node()
                self.right.change(root.right, node1, node2)
        self.size = 1
        if self.left:
            self.size += self.left.size
        if self.right:
            self.size += self.right.size

    def getNodes(self):
        ret = []
        if self.left:
            ret += self.left.getNodes()
        ret.append(self)
        if self.right:
            ret += self.right.getNodes()
        return ret

    def __str__(self):
        if self.val in T:
            if self.val[0] == 'c':
                return str(C[int(self.val[1])]) 
            else:
                return str(self.val)
        if self.val == "sin" or self.val == "cos":
            return self.val + "(" + str(self.left) + ")"
        return str(self.left) + self.val + str(self.right)

    def __repr__(self):
        return self.__str__()