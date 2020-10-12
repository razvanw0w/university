from lab8.repository import Repository
from lab8.controller import Controller
from lab8.ui import UI

repo = Repository("regression.data")
controller = Controller(repo)
ui = UI(controller)
ui.run()