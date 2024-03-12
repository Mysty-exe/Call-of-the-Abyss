import pygame
from Project.math import Vector

class Tile:
    width = 32
    height = 32

    def __init__(self, tileType, map_location, world_location):
        self.tileType = tileType
        self.map_location = map_location
        self.world_location = world_location
        self.tile = pygame.image.load("Assets/Tiles/grass.png").convert_alpha()

    def drawTile(self, surface):
        surface.blit(self.tile, self.world_location.toTuple())
