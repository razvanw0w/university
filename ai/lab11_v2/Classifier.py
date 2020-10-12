class Classifier:
    def classify(value):
        if value <= -5:
            return 'Slight-Right-Turn'
        elif -5 < value <= 0:
            return 'Sharp-Right-Turn'
        elif 0 < value <= 5:
            return 'Move-Forward'
        else:
            return 'Slight-Left-Turn'