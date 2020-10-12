from copy import deepcopy
import math

class DTNode:
    def __init__(self, parent, instances, allowedAttributes):
        self.neighbours = {}
        self.decisionNode = True
        self.parent = parent
        self.instances = deepcopy(instances)
        self.nodeAttribute = None
        self.allowedAttributes = deepcopy(allowedAttributes)
        self.classType = None

    def initDecisionNode(self, nodeAttribute):
        self.decisionNode = True
        self.nodeAttribute = nodeAttribute

    def initClassNode(self, classType):
        self.decisionNode = False
        self.classType = classType

    def addNeighbour(self, nodeAttributeValue, node):
        self.neighbours[nodeAttributeValue] = node