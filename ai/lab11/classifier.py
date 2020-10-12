# -*- coding: utf-8 -*-

class Classifier:
    @staticmethod
    def classify(value):
        if value <= -1:
            return "Slight-Right-Turn"
        elif -1 < value <= 0:
            return "Sharp-Right-Turn"
        elif 0 < value <= 1:
            return "Move-Forward"
        else:
            return "Slight-Left-Turn"