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


def createDecisionTree(instances):
    root = DTNode(None, instances, [1, 2, 3, 4])
    dfs(root)
    return root


def getClassOccurencesDict(instances):
    occurences = {'B': 0, 'L': 0, 'R': 0}
    for instance in instances:
        occurences[instance[0]] += 1
    return occurences


def getClassProportionDict(instances):
    proportion = getClassOccurencesDict(instances)
    for key in proportion.keys():
        proportion[key] /= len(instances)
    return proportion


def getEntropy(instances):
    proportion = getClassProportionDict(instances)
    sum = 0
    for key in proportion.keys():
        if proportion[key] > 0:
            sum += proportion[key] * math.log2(proportion[key])
    return sum * (-1)


def getAttributeGain(instances, attribute, nodeEntropy):
    sum = 0
    n = len(instances)
    for value in range(1, 6):
        filtered = [x for x in instances if x[attribute] == value]
        m = len(filtered)
        if m > 0:
            sum += m / n * getEntropy(filtered)
    return nodeEntropy - sum


def hasOnlyOneClass(instances):
    occurences = getClassOccurencesDict(instances)
    n = len(instances)
    if occurences['B'] == n:
        return 'B'
    if occurences['L'] == n:
        return 'L'
    if occurences['R'] == n:
        return 'R'
    return None


def mostAppearingClass(instances):
    occurences = getClassOccurencesDict(instances)
    return max(occurences.keys(), key=lambda x: occurences[x])


def canBeClassNode(node):
    if len(node.instances) == 0:
        node.initClassNode(mostAppearingClass(node.parent.instances))
        return True
    if len(node.allowedAttributes) == 0:
        node.initClassNode(mostAppearingClass(node.instances))
        return True
    clazz = hasOnlyOneClass(node.instances)
    if clazz is not None:
        node.initClassNode(clazz)
        return True
    return False


def dfs(node):
    if not canBeClassNode(node):
        nodeEntropy = getEntropy(node.instances)
        selectedAttribute = min(node.allowedAttributes, key=lambda x: getAttributeGain(node.instances, x, nodeEntropy))
        node.initDecisionNode(selectedAttribute)
        newAllowedAttributes = [x for x in node.allowedAttributes if x != selectedAttribute]
        for value in range(1, 6):
            newInstances = [x for x in node.instances if x[selectedAttribute] == value]
            newNode = DTNode(node, newInstances, newAllowedAttributes)
            node.addNeighbour(value, newNode)
        for value in range(1, 6):
            dfs(node.neighbours[value])
