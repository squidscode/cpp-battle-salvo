#include "AIVSAIFactory.hpp"
#include "../../model/player/ai_player/AIPlayer.hpp"
#include "../../model/player/manual_player/ManualPlayer.hpp"
#include "../../model/player/strategies/setup/random/RandomSetup.hpp"
#include "../../model/player/strategies/shot/random/RandomShot.hpp"
#include "../../controller/player_controller/PlayerController.hpp"
#include "../../view/board_viewer/colored/ColoredBoardViewer.hpp"
#include "../../view/board_viewer/fancy/FancyBoardViewer.hpp"
#include "../../controller/game_controller/GameController.hpp"
#include <iostream>

using namespace Factory;

AIVSAIFactory::AIVSAIFactory(Model::SetupStrategy *setup1, Model::SetupStrategy *setup2,
    Model::ShotStrategy *shot1, Model::ShotStrategy *shot2) {
    this->boardViewer = new View::ColoredBoardViewer();
    this->view = new View::TextView(this->boardViewer, &std::cin, &std::cout);

    this->playerObserver = new Controller::PlayerController(this->view);

    char name1[] = "Player 1";
    char name2[] = "Player 2";
    
    this->aiFactory1 = new Factory::AIPlayerFactory(name1, setup1, shot1);
    this->aiFactory2 = new Factory::AIPlayerFactory(name2, setup2, shot2);
    this->aiFactory1->AttachPlayerObserver(this->playerObserver);

    this->model = new Model::BattleSalvoGame(this->aiFactory1->CreatePlayer(), this->aiFactory2->CreatePlayer());

    this->controller = new Controller::GameController(this->view, this->model);
}

AIVSAIFactory::AIVSAIFactory() : AIVSAIFactory(new RandomSetup, new RandomSetup, new RandomShot, new RandomShot) {}

AIVSAIFactory::~AIVSAIFactory() {
    delete boardViewer;
    delete view;
    delete controller;
    delete playerObserver;
    delete model;
    delete aiFactory1;
    delete aiFactory2;
}

View::View *AIVSAIFactory::CreateView() {
    return this->view;
}

Controller::Controller *AIVSAIFactory::CreateController() {
    return this->controller;
}

Model::BattleSalvoGame *AIVSAIFactory::CreateBattleSalvoGame() {
    return this->model;
}
