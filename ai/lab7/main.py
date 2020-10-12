from lab7.repository import Repository
from lab7.controller import Controller
from lab7.ui import UI

repo = Repository("regression.data")
controller = Controller(repo)
ui = UI(controller)
ui.run()