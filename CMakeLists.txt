cmake_minimum_required(VERSION 3.19)
project(Main)
set(CMAKE_CXX_STANDARD 20)
include_directories(Headers Images Sounds)

add_executable(Main Main.cpp Game.cpp State.cpp
               MainMenuState.cpp TextureManager.cpp
               GameState.cpp OptionsState.cpp Button.cpp
               Obsticle.cpp Cactus.cpp Bird.cpp Player.cpp
               SoundManager.cpp)
target_link_libraries(Main sfml-graphics sfml-window sfml-system sfml-audio)
