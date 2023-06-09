#include "HumanVsAIFactory.hpp"
#include "../../model/player/ai_player/AIPlayer.hpp"
#include "../../model/player/manual_player/ManualPlayer.hpp"
#include "../../model/player/strategies/setup/random/RandomSetup.hpp"
#include "../../model/player/strategies/shot/random/RandomShot.hpp"
#include "../../controller/PlayerController.hpp"
#include "../../view/board_viewer/colored/ColoredBoardViewer.hpp"
#include "../../view/board_viewer/fancy/FancyBoardViewer.hpp"
#include "../../controller/GameController.hpp"
#include <iostream>

using namespace Factories;

HumanVsAIFactory::HumanVsAIFactory() {
    this->boardViewer = new View::ColoredBoardViewer();
    this->view = new View::TextView(this->boardViewer, &std::cin, &std::cout);

    this->setupStrat = new Model::RandomSetup();
    this->shotStrat = new Model::RandomShot();
    this->playerObserver = new Controller::PlayerController(this->view);

    char name1[] = "Player 1";
    char name2[] = "Player 2";
    // Model::ObservablePlayer *obPlay = new Model::ManualPlayer(name1, this->setupStrat, this->view);
    Model::ObservablePlayer *obPlay = new Model::AIPlayer(name1, this->setupStrat, this->shotStrat);
    this->player1 = obPlay;
    this->player2 = new Model::AIPlayer(name2, this->setupStrat, this->shotStrat);
    this->model = new Model::BattleSalvoGame(this->player1, this->player2);

    obPlay->Attach(this->playerObserver);

    this->controller = new Controller::GameController(this->view, this->model);
}

// TODO: Virtual destructors??
HumanVsAIFactory::~HumanVsAIFactory() {
    delete ((View::ColoredBoardViewer*) boardViewer);
    delete ((View::TextView*) view);
    delete (controller);
    delete playerObserver;
    delete model;
    delete player1;
    delete player2;
    delete setupStrat;
    delete shotStrat;
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
