#include "ControllerImpl.hpp"
#include <string>

#define min(x,y)    x < y ? x : y    

using namespace Controller;

ControllerImpl::ControllerImpl(View::View *view, Model::BattleSalvoGame *game) {
    this->view = view;
    this->game = game;
}

// CARRIER=6, BATTLESHIP=5, DESTROYER=4, SUBMARINE=3

void ControllerImpl::Run() {
    int widthAndHeight[2] = {-1, -1};
    int shipTypeFreq[4] = {-1, -1, -1, -1};
    this->view->DisplayWelcomeMessage();
    this->view->ReadWidthAndHeight(widthAndHeight);
    while(!(6 <= widthAndHeight[0] && widthAndHeight[0] <= 15) 
        || !(6 <= widthAndHeight[1] && widthAndHeight[1] <= 15)){
        this->view->DisplayMessage("ERROR: Invalid width/height."
            "\nWidth and height must both be within the range [6, 14] inclusive.");
        this->view->ReadWidthAndHeight(widthAndHeight);
    }
    int minWH = min(widthAndHeight[0], widthAndHeight[1]);
    std::string warning = "Select values for ship frequency as a line of positive numbers with a sum less than " 
        + std::to_string(minWH) + ".\n";
    this->view->DisplayMessage((warning + "Format: \"NUM-CARRIERS NUM-BATTLESHIPS NUM-DESTROYERS NUM-SUBMARINES\"").c_str());
    this->view->ReadShipTypeFrequency(shipTypeFreq, 4);
    while(shipTypeFreq[0] <= 0 || shipTypeFreq[1] <= 0 || shipTypeFreq[2] <= 0 
        || shipTypeFreq[3] <= 0 || shipTypeFreq[0] + shipTypeFreq[1] + shipTypeFreq[2] + shipTypeFreq[3] > minWH){
        this->view->DisplayMessage(("ERROR: Invalid frequency.\n" + warning).c_str());
        this->view->ReadShipTypeFrequency(shipTypeFreq, 4);
    }
    Map<Model::ShipType, int> map;
    map.Insert(Model::ShipType::CARRIER, shipTypeFreq[0]);
    map.Insert(Model::ShipType::BATTLESHIP, shipTypeFreq[1]);
    map.Insert(Model::ShipType::DESTROYER, shipTypeFreq[2]);
    map.Insert(Model::ShipType::SUBMARINE, shipTypeFreq[3]);
    this->game->Setup(widthAndHeight[0], widthAndHeight[1], &map);
    while(!this->game->GameOver()) {
        this->game->GameStep();
    }
}