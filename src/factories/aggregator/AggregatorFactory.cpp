#include "AggregatorFactory.hpp"
#include "../../model/player/ai_player/AIPlayer.hpp"
#include "../../model/player/manual_player/ManualPlayer.hpp"
#include "../../model/player/strategies/setup/random/RandomSetup.hpp"
#include "../../model/player/strategies/shot/random/RandomShot.hpp"
#include "../../controller/player_controller/PlayerController.hpp"
#include "../../view/board_viewer/colored/ColoredBoardViewer.hpp"
#include "../../view/board_viewer/fancy/FancyBoardViewer.hpp"
#include "../../controller/game_aggregator/GameAggregatorController.hpp"
#include <iostream>
#include <stdexcept>

using namespace Factory;

AggregatorFactory::AggregatorFactory(int numTimes, Model::SetupStrategy* setup1, 
    Model::SetupStrategy* setup2, Model::ShotStrategy* shot1, Model::ShotStrategy* shot2) {
    this->boardViewer = new View::ColoredBoardViewer();
    this->view = new View::TextView(this->boardViewer, &std::cin, &std::cout);

    char name1[] = "Player 1";
    char name2[] = "Player 2";
    
    this->aiFactory1 = new Factory::AIPlayerFactory(name1, setup1, shot1);
    this->aiFactory2 = new Factory::AIPlayerFactory(name2, setup2, shot2);

    this->controller = new Controller::GameAggregatorController(this->view, numTimes, aiFactory1, aiFactory2);
}

AggregatorFactory::~AggregatorFactory() {
    delete boardViewer;
    delete view;
    delete controller;
    delete aiFactory1;
    delete aiFactory2;
}

View::View *AggregatorFactory::CreateView() {
    return this->view;
}

Controller::Controller *AggregatorFactory::CreateController() {
    return this->controller;
}

Model::BattleSalvoGame *AggregatorFactory::CreateBattleSalvoGame() {
    throw std::runtime_error("An aggregator factory cannot return a single BattleSalvoGame!");
    return nullptr;
}
