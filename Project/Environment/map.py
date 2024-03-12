from Project.Environment.tile import Tile
from Project.math import Vector

class Map:
    
    def __init__(self, name, map_dir):
        self.name = name
        self.map_dir = map_dir
        self.map_tiles = []
        self.mapCoords = Vector(600, 200)
        self.loadMap()

    def loadMap(self):
        mapX, mapY = self.mapCoords.x, self.mapCoords.y

        with open(self.map_dir) as f:
            rows = [line.rstrip('\n') for line in f]
            for rowNumber, row in enumerate(rows):
                self.map_tiles.append([])
                tileIncrement = 0
                for columnNumber, tileType in reversed(list(enumerate(row))):
                    tileIncrement += 1
                    if tileType != " ":
                        map_location = Vector(rowNumber + 1, columnNumber + 1)
                        world_location = Vector(mapX, mapY)
                        tile = Tile(tileType, map_location, world_location)
                        self.map_tiles[-1].append(tile)

                    mapX -= Tile.width / 2
                    mapY += Tile.height / 4

                mapX = self.mapCoords.x + (Tile.width / 2 * (rowNumber + 1))
                mapY = self.mapCoords.y + (Tile.height / 4 * (rowNumber + 1))
        

    def printMap(self):
        for row in self.map_tiles:
            for tile in row:
                print("0", end=" ")
            print()
        print()

    def drawMap(self, surface):
        for row in self.map_tiles:
            for tile in row:
                tile.drawTile(surface)
