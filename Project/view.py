import pygame
import random
from Project.math import Vector
from Project.Environment.map import Map
from Project.helpers import Helpers

class View:
 
    def __init__(self):
        self.width, self.height = Helpers.width, Helpers.height
        self.screen = pygame.display.set_mode((self.width, self.height), 0, 32)
        self.display = pygame.Surface((self.width, self.height))
        self.timer = 0

        self.map = Map('Test Map', 'Maps/test_map.txt')

    def main_menu(self):
        pass

    def run(self, dt, state, events):
        self.screen.blit(self.display, (0, 0))
        self.display.fill(Helpers.colours["White"])
        self.map.drawMap(self.display)

        for event in events:
            pass

        return state
