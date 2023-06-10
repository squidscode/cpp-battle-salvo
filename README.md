Link to project description: https://markefontenot.notion.site/PA-03-BattleSalvo-Part-1-81f5240ddb3b4a38a491f1215abbdab4

I'm going to writing out all of the code in C++ rather than Java because I enjoy C++ more. It should also prevent any students from misusing my code because they would have to spend the time to transpile my code to Java before they turn it in (which I suppose is possible, but it just seems like a lot of effort). 


# Project Structure
```
.
├── CMakeLists.txt
├── Driver.cpp
├── controller
│   ├── Controller.hpp
│   ├── commands
│   │   └── BattleSalvoGameCommand.hpp
│   ├── game_aggregator
│   │   ├── GameAggregatorController.cpp
│   │   └── GameAggregatorController.hpp
│   ├── game_controller
│   │   ├── GameController.cpp
│   │   └── GameController.hpp
│   └── player_controller
│       ├── PlayerController.cpp
│       └── PlayerController.hpp
├── factories
│   ├── GameFactory.hpp
│   ├── aggregator
│   │   ├── AggregatorFactory.cpp
│   │   └── AggregatorFactory.hpp
│   ├── ai_vs_ai
│   │   ├── AIVSAIFactory.cpp
│   │   └── AIVSAIFactory.hpp
│   ├── human_vs_ai
│   │   ├── HumanVsAIFactory.cpp
│   │   └── HumanVsAIFactory.hpp
│   └── player_factories
│       ├── PlayerFactory.cpp
│       ├── PlayerFactory.hpp
│       ├── ai_player_factory
│       │   ├── AIPlayerFactory.cpp
│       │   └── AIPlayerFactory.hpp
│       └── manual_player_factory
│           ├── ManualPlayerFactory.cpp
│           └── ManualPlayerFactory.hpp
├── model
│   ├── BattleSalvoGame.cpp
│   ├── BattleSalvoGame.hpp
│   ├── BattleSalvoRound.cpp
│   ├── BattleSalvoRound.hpp
│   ├── GamePlayer.hpp
│   ├── GameResult.hpp
│   ├── board
│   │   ├── Board.cpp
│   │   ├── Board.hpp
│   │   ├── Ship.cpp
│   │   ├── Ship.hpp
│   │   └── ShipType.hpp
│   └── player
│       ├── ObservablePlayer.cpp
│       ├── ObservablePlayer.hpp
│       ├── Player.hpp
│       ├── PlayerObserver.hpp
│       ├── PlayerSnapshot.cpp
│       ├── PlayerSnapshot.hpp
│       ├── PlayerStatus.hpp
│       ├── ai_player
│       │   ├── AIPlayer.cpp
│       │   └── AIPlayer.hpp
│       ├── generic_player
│       │   ├── GenericPlayer.cpp
│       │   └── GenericPlayer.hpp
│       ├── manual_player
│       │   ├── ManualPlayer.cpp
│       │   └── ManualPlayer.hpp
│       └── strategies
│           ├── setup
│           │   ├── SetupStrategy.hpp
│           │   └── random
│           │       ├── RandomSetup.cpp
│           │       └── RandomSetup.hpp
│           └── shot
│               ├── ShotStrategy.hpp
│               ├── entropy_max
│               ├── heat_map
│               │   ├── HeatMap.cpp
│               │   └── HeatMap.hpp
│               ├── random
│               │   ├── RandomShot.cpp
│               │   └── RandomShot.hpp
│               └── scatter
├── util
│   ├── Iterator.hpp
│   ├── Iterator.tpp
│   └── Map.hpp
└── view
    ├── ShotReadable.hpp
    ├── TextView.cpp
    ├── TextView.hpp
    ├── View.hpp
    └── board_viewer
        ├── BoardViewer.hpp
        ├── colored
        │   ├── ColoredBoardViewer.cpp
        │   └── ColoredBoardViewer.hpp
        ├── fancy
        │   ├── FancyBoardViewer.cpp
        │   └── FancyBoardViewer.hpp
        └── plain
            └── PlainBoardViewer.hpp
```

# Contributing
Add a strategy to the "src/model/player/strategies" folder and change `Driver.cpp` to allow access to the strategy. Use `./run_battle_salvo --aggregate 1000 SETUP#1 SETUP#2 SHOT#1 SHOT#2` to test.

Current best: `heatmap-shotxR-0-10`.