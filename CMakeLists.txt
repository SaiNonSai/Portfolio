cmake_minimum_required(VERSION 3.14)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# set(CMAKE_PREFIX_PATH C:/)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/Server.h src/Server.cpp src/Client.h src/CLient.cpp
        src/FreeFuncs.cpp
        src/ImageLayer.cpp
        src/LayerGroup.cpp
        src/Map.cpp
        src/meson.build
        src/miniz.c
        src/miniz.h
        src/Object.cpp
        src/ObjectTypes.cpp
        src/ObjectGroup.cpp
        src/Property.cpp
        src/Tileset.cpp
        src/TileLayer.cpp
        src/detail/pugixml.cpp
        src/detail/pugixml.hpp
        src/Tile.h src/Tile.cpp src/Server.cpp src/Server.h src/Client.cpp src/Client.h src/Player.cpp src/Player.h src/Vector.cpp src/Vector.h src/GameStats.h src/Ui.cpp src/Ui.h src/GameObject.cpp src/GameObject.h src/Villager.cpp src/Villager.h)
add_executable(SFMLGame ${SOURCE_FILES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (SFMLGame sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)
