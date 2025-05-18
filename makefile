CXX = g++
CXXFLAGS = -std=c++20 -I./include -I./libs -I./libs/SDL2/include -I./libs/SDL2Image/include -I./libs/SDL2TTF/include -I./libs/SDL2Mixer/include
LDFLAGS = -L./libs/SDL2/lib -L./libs/SDL2Image/lib -L./libs/SDL2TTF/lib -L./libs/SDL2Mixer/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Target executable name
TARGET = build/main.exe

# Source files
SRC_FILES = src/main.cpp src/Tools/Utilities.cpp src/Tools/Timer.cpp src/Tools/Camera.cpp src/Math/Vector.cpp \
			src/Managers/Manager.cpp src/Managers/MessageManager.cpp src/Managers/EventManager.cpp src/Managers/StateManager.cpp src/Managers/MenuManager.cpp src/Managers/GameManager.cpp src/Managers/SettingsManager.cpp \
			src/Model/Entities/Entity.cpp src/Model/Entities/Player.cpp src/Model/Entities/Enemy.cpp \
			src/Model/Dungeon/Floor.cpp src/Model/Dungeon/Room.cpp src/Model/Dungeon/Tile.cpp \
			src/Model/Combat/Weapon.cpp \
			src/UI/Texture.cpp src/UI/Animation.cpp src/UI/GameUI/Healthbar.cpp

# Rule to build the target
$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(TARGET) $(LDFLAGS)

# Run the executable
run: $(TARGET)
	$(TARGET)

# Clean up generated files
clean:
	del /f /q $(TARGET)
