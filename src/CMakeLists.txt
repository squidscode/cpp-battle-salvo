cmake_minimum_required(VERSION 3.13)  # CMake version check
project(BattleSalvoC++)               # Create project "BattleSalvoC++"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES ../src/controller/PlayerController.cpp ../src/controller/GameController.cpp
    ../src/controller/GameAggregatorController.cpp ../src/Driver.cpp
    ../src/factories/pa03/HumanVsAIFactory.cpp ../src/model/board/Board.cpp
    ../src/model/board/Ship.cpp ../src/model/BattleSalvoGame.cpp
    ../src/model/player/strategies/setup/random/RandomSetup.cpp ../src/model/player/strategies/shot/random/RandomShot.cpp
    ../src/model/player/manual_player/ManualPlayer.cpp ../src/model/player/ai_player/AIPlayer.cpp
    ../src/model/player/PlayerSnapshot.cpp ../src/model/player/ObservablePlayer.cpp
    ../src/model/player/generic_player/GenericPlayer.cpp ../src/view/board_viewer/colored/ColoredBoardViewer.cpp
    ../src/view/board_viewer/fancy/FancyBoardViewer.cpp ../src/view/TextView.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(run_battle_salvo ${SOURCE_FILES})