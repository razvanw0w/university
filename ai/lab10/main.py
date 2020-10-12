from lab10.repository import Repository
from lab10.controller import Controller
from lab10.logger import Logger
from lab10.ui import UI

Logger.filename = 'description.txt'
repo = Repository()
repo.loadDescriptions('problem_descr.in')
repo.loadRules('problem_rules.in')
ctrl = Controller(repo)
#print(ctrl.compute({'temperature': 120, 'capacity': 1}))
ui = UI(ctrl, 'input.in', 'output.out')
ui.run()