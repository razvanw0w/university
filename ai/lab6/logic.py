from lab6.dt import DTNode
import math

class DT:
    @staticmethod
    def createDecisionTree(instances):
        root = DTNode(None, instances, [1, 2, 3, 4])
        DT.dfs(root)
        return root

    @staticmethod
    def getClassOccurencesDict(instances):
        occurences = {'B': 0, 'L': 0, 'R': 0}
        for instance in instances:
            occurences[instance[0]] += 1
        return occurences

    @staticmethod
    def getClassProportionDict(instances):
        proportion = DT.getClassOccurencesDict(instances)
        for key in proportion.keys():
            proportion[key] /= len(instances)
        return proportion

    @staticmethod
    def getEntropy(instances):
        proportion = DT.getClassProportionDict(instances)
        sum = 0
        for key in proportion.keys():
            if proportion[key] > 0:
                sum += proportion[key] * math.log2(proportion[key])
        return sum * (-1)

    @staticmethod
    def getAttributeGain(instances, attribute, nodeEntropy):
        sum = 0
        n = len(instances)
        for value in range(1, 6):
            filtered = [x for x in instances if x[attribute] == value]
            m = len(filtered)
            if m > 0:
                sum += m / n * DT.getEntropy(filtered)
        return nodeEntropy - sum

    @staticmethod
    def hasOnlyOneClass(instances):
        occurences = DT.getClassOccurencesDict(instances)
        n = len(instances)
        if occurences['B'] == n:
            return 'B'
        if occurences['L'] == n:
            return 'L'
        if occurences['R'] == n:
            return 'R'
        return None

    @staticmethod
    def mostAppearingClass(instances):
        occurences = DT.getClassOccurencesDict(instances)
        return max(occurences.keys(), key=lambda x: occurences[x])

    @staticmethod
    def canBeClassNode(node):
        if len(node.instances) == 0:
            node.initClassNode(DT.mostAppearingClass(node.parent.instances))
            return True
        if len(node.allowedAttributes) == 0:
            node.initClassNode(DT.mostAppearingClass(node.instances))
            return True
        clazz = DT.hasOnlyOneClass(node.instances)
        if clazz is not None:
            node.initClassNode(clazz)
            return True
        return False

    @staticmethod
    def dfs(node):
        if not DT.canBeClassNode(node):
            nodeEntropy = DT.getEntropy(node.instances)
            selectedAttribute = min(node.allowedAttributes,
                                    key=lambda x: DT.getAttributeGain(node.instances, x, nodeEntropy))
            node.initDecisionNode(selectedAttribute)
            newAllowedAttributes = [x for x in node.allowedAttributes if x != selectedAttribute]
            for value in range(1, 6):
                newInstances = [x for x in node.instances if x[selectedAttribute] == value]
                newNode = DTNode(node, newInstances, newAllowedAttributes)
                node.addNeighbour(value, newNode)
            for value in range(1, 6):
                DT.dfs(node.neighbours[value])

class Tester:
    @staticmethod
    def getClass(node, instance):
        if not node.decisionNode:
            return node.classType
        return Tester.getClass(node.neighbours[instance[node.nodeAttribute]], instance)

    @staticmethod
    def getCorrectClass(instance):
        answer = instance[1] * instance[2] - instance[3] * instance[4]
        if answer < 0:
            return 'R'
        if answer > 0:
            return 'L'
        return 'B'

    @staticmethod
    def testInstances(testData, root):
        n = len(testData)
        for i in range(n):
            clazz = Tester.getClass(root, testData[i])
            testData[i][0] = clazz
        return testData

    @staticmethod
    def getAccuracy(tested):
        correct = 0
        for instance in tested:
            correctClass = Tester.getCorrectClass(instance)
            if instance[0] == correctClass:
                correct += 1
            #     print('GOOD', instance, "correct =", correctClass)
            # else:
            #     print(' BAD', instance, "correct =", correctClass)

        return correct * 100 / len(tested)