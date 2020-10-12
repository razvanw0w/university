class Utils:
    @staticmethod
    def trapezoidalRegion(a, b, c, d):
        return lambda x: max(0, min((x - a) / (b - a), 1, (d - x) / (d - c)))

    @staticmethod
    def triangularRegion(a, b, c):
        return Utils.trapezoidalRegion(a, b, b, c)

    @staticmethod
    def inverseLine(a, b):
        return lambda value: value * (b - a) + a

    @staticmethod
    def inverseTriangular(a, b, c):
        return lambda value: (Utils.inverseLine(a, b)(value) + Utils.inverseLine(c, b)(value)) / 2