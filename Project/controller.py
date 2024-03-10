import pygame
import Project.helpers as helpers
import sys
from Project.view import View

class GameInstance:

    def __init__(self):
        pygame.init()

        self.title = helpers.GAME_TITLE
        # self.icon = pygame.image.load('assets/icon.png')

        pygame.display.set_caption(self.title)
        # pygame.display.set_icon(self.icon)

        self.game_state = 'Game'
        self.game = View()

        self.fps = helpers.GAME_FPS
        self.dt = self.fps
        self.clock = pygame.time.Clock()

    def run(self):
        while self.game_state != 'Quit':
            events = pygame.event.get()

            for event in events:
                if event.type == pygame.QUIT:
                    self.game_state = 'Quit'

            if self.game_state == 'Game':
                self.game_state = self.game.run(self.dt, self.game_state, events)

            pygame.display.update()
            self.dt = (self.clock.tick(self.fps) / 1000) * 60

        self.quit()

    def quit(self):
        pygame.quit()
        sys.exit()
