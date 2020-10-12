from lab9.ui import UI
from lab9.controller import Controller
from lab9.repository import Repository

repo = Repository()
controller = Controller(repo, True)
ui = UI(controller)
ui.run()