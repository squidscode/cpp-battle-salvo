cmake_minimum_required(VERSION 3.13)  # CMake version check
project(BattleSalvoC++)
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# don't run the JSON_BuildTests
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES ../src/controller/player_controller/PlayerController.cpp ../src/controller/proxy_controller/ProxyController.cpp ../src/controller/game_controller/GameController.cpp ../src/controller/game_aggregator/GameAggregatorController.cpp ../src/Driver.cpp ../src/factories/ai_vs_ai/AIVSAIFactory.cpp ../src/factories/aggregator/AggregatorFactory.cpp ../src/factories/server/ServerFactory.cpp ../src/factories/human_vs_ai/HumanVsAIFactory.cpp ../src/factories/player_factories/manual_player_factory/ManualPlayerFactory.cpp ../src/factories/player_factories/ai_player_factory/AIPlayerFactory.cpp ../src/factories/player_factories/PlayerFactory.cpp ../src/model/board/Board.cpp ../src/model/board/Ship.cpp ../src/model/BattleSalvoRound.cpp ../src/model/BattleSalvoGame.cpp ../src/model/player/strategies/setup/random/RandomSetup.cpp ../src/model/player/strategies/shot/heat_map/HeatMap.cpp ../src/model/player/strategies/shot/random/RandomShot.cpp ../src/model/player/manual_player/ManualPlayer.cpp ../src/model/player/ai_player/AIPlayer.cpp ../src/model/player/PlayerSnapshot.cpp ../src/model/player/ObservablePlayer.cpp ../src/model/player/generic_player/GenericPlayer.cpp ../src/view/board_viewer/colored/ColoredBoardViewer.cpp ../src/view/board_viewer/fancy/FancyBoardViewer.cpp ../src/view/TextView.cpp )

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(run_battle_salvo ${SOURCE_FILES})
target_link_libraries(run_battle_salvo PRIVATE nlohmann_json::nlohmann_json)
