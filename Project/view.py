import pygame
import Project.helpers as helpers
import random
from Project.math import Vector

class View:
 
    def __init__(self):
        self.width, self.height = helpers.GAME_WIDTH, helpers.GAME_HEIGHT
        self.screen = pygame.display.set_mode((self.width, self.height), 0, 32)
        self.display = pygame.Surface((self.width, self.height))
        self.timer = 0

    def main_menu(self):
        pass

    def run(self, dt, state, events):
        self.display.fill(helpers.COLOURS["Black"])
        self.screen.blit(self.display, (0, 0))

        for event in events:
            pass

        return state
