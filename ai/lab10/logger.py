class Logger:
    filename = None

    @staticmethod
    def log(descr, message):
        f = open(Logger.filename, "a")
        f.write(descr + ': ' + message + "\n")
        f.close()