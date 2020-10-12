from lab10.logger import Logger

class Controller:
    def __init__(self, repo):
        self.repo = repo

    def compute(self, inputs):
        system = self.repo.getSystem()
        Logger.log('=== BEGAN COMPUTATION FOR INPUT', str(inputs))
        output = system.compute(inputs)
        Logger.log('>>> OBTAINED OUTPUT PARAMETER', str(output))
        return output