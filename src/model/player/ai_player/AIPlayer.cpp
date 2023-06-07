#include "AIPlayer.hpp"

using namespace Model;

AIPlayer::AIPlayer(char* name, SetupStrategy* setup, ShotStrategy* shot) : GenericPlayer{name} {
    this->setupStrategy = setup;
    this->shotStrategy = shot;
}

// Player Interface overriding:
Iterator<Ship> AIPlayer::Setup(int width, int height, Map<ShipType, int> *specifications) {
    this->NotifyObservers(&PlayerObserver::PreSetup);
    Iterator<Ship> ret = this->setupStrategy->BuildSetup(width, height, specifications);
    this->myBoard = new Board(width, height);
    this->opponentBoard = new Board(width, height);
    this->SetShips(ret);
    this->NotifyObservers(&PlayerObserver::PostSetup);
    return ret;
}

Iterator<std::pair<int,int>> AIPlayer::TakeShots() {
    this->NotifyObservers(&PlayerObserver::PreTakeShots);
    auto ret = this->shotStrategy->BuildShots(this->ShipsAlive(), *this->opponentBoard);
    this->UpdateShots(ret);
    this->NotifyObservers(&PlayerObserver::PostTakeShots);
    return ret;
}

