#include "HumanVsAIFactory.hpp"
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

HumanVsAIFactory::HumanVsAIFactory(Model::SetupStrategy *setup, Model::ShotStrategy *shot) {
    this->boardViewer = new View::ColoredBoardViewer();
    this->view = new View::TextView(this->boardViewer, &std::cin, &std::cout);

    this->setupStrat = setup;
    this->shotStrat = shot;
    this->playerObserver = new Controller::PlayerController(this->view);

    char name1[] = "Player 1";
    char name2[] = "Player 2";
    
    this->manualFactory = new Factory::ManualPlayerFactory(name1, this->setupStrat, this->view);
    this->aiFactory = new Factory::AIPlayerFactory(name2, this->setupStrat, this->shotStrat);
    this->manualFactory->AttachPlayerObserver(this->playerObserver);

    this->model = new Model::BattleSalvoGame(this->manualFactory->CreatePlayer(), this->aiFactory->CreatePlayer());

    this->controller = new Controller::GameController(this->view, this->model);

}

HumanVsAIFactory::HumanVsAIFactory(Model::SetupStrategy *setup) : HumanVsAIFactory(setup, new RandomShot) {};

HumanVsAIFactory::HumanVsAIFactory(Model::ShotStrategy *shot) : HumanVsAIFactory(new RandomSetup, shot) {}

HumanVsAIFactory::HumanVsAIFactory() : HumanVsAIFactory(new RandomSetup(), new RandomShot()) {}

HumanVsAIFactory::~HumanVsAIFactory() {
    delete boardViewer;
    delete view;
    delete controller;
    delete playerObserver;
    delete model;
    delete manualFactory;
    delete aiFactory;
}

View::View *HumanVsAIFactory::CreateView() {
    return this->view;
}

Controller::Controller *HumanVsAIFactory::CreateController() {
    return this->controller;
}

Model::BattleSalvoGame *HumanVsAIFactory::CreateBattleSalvoGame() {
    return this->model;
}
