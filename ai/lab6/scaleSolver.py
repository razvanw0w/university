def getClass(node, instance):
    if not node.decisionNode:
        return node.classType
    return getClass(node.neighbours[instance[node.nodeAttribute]], instance)


def getCorrectClass(instance):
    answer = instance[1] * instance[2] - instance[3] * instance[4]
    if answer < 0:
        return 'R'
    if answer > 0:
        return 'L'
    return 'B'


def testInstances(testData, root):
    n = len(testData)
    for i in range(n):
        clazz = getClass(root, testData[i])
        testData[i][0] = clazz
    return testData


def getAccuracy(tested):
    correct = 0
    for instance in tested:
        correctClass = getCorrectClass(instance)
        if instance[0] == correctClass:
            correct += 1
        #     print('GOOD', instance, "correct =", correctClass)
        # else:
        #     print(' BAD', instance, "correct =", correctClass)

    return correct * 100 / len(tested)
