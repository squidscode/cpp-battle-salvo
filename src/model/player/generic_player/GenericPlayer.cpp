#include "GenericPlayer.hpp"
#include <cstddef>

using namespace Model;

GenericPlayer::GenericPlayer(char* name) {
    strcpy(this->name, name);
    this->myBoard = nullptr;
    this->opponentBoard = nullptr;
}

// Rule of 3:
GenericPlayer::~GenericPlayer() {
    if(this->myBoard != nullptr) delete this->myBoard;
    if(this->opponentBoard != nullptr) delete this->opponentBoard;
}

GenericPlayer::GenericPlayer(const GenericPlayer& other) {
    assert(this->myBoard != other.myBoard);
    assert(this->opponentBoard != other.opponentBoard);
    if(this->myBoard != nullptr) delete this->myBoard;
    if(this->opponentBoard != nullptr) delete this->opponentBoard;
    this->myBoard = new Board(*other.myBoard);
    this->opponentBoard = new Board(*other.opponentBoard);
}

GenericPlayer& GenericPlayer::operator=(const GenericPlayer& other) {
    if(this->myBoard != nullptr) delete this->myBoard;
    if(this->opponentBoard != nullptr) delete this->opponentBoard;
    this->myBoard = new Board(*other.myBoard);
    this->opponentBoard = new Board(*other.opponentBoard);
    return *this;
}

// Player Interface overriding:
const char* GenericPlayer::Name() {
    return this->name;
}

Iterator<std::pair<int, int>> GenericPlayer::ReportDamage(Iterator<std::pair<int, int>> *opponentShots) {
    this->NotifyObservers(&PlayerObserver::PreReportDamage);
    std::vector<std::pair<int,int>> hits;
    while(opponentShots->HasNext()) {
        std::pair<int,int> coord = opponentShots->Next();
        assert(this->myBoard->ValidPosition(coord.first, coord.second));
        if(this->myBoard->GetCell(coord.first, coord.second) == CellType::SHIP){
            hits.push_back(coord);
            this->myBoard->SetCell(coord.first, coord.second, CellType::HIT);
        } else {
            this->myBoard->SetCell(coord.first, coord.second, CellType::MISS);
        }
    }
    this->NotifyObservers(&PlayerObserver::PostReportDamage);
    return Iterator<std::pair<int,int>>(hits);
}

void GenericPlayer::SuccessfulHits(Iterator<std::pair<int,int>> *successfulShots) {
    this->NotifyObservers(&PlayerObserver::PreSuccessfulHits);
    while(successfulShots->HasNext()) {
        std::pair<int,int> coord = successfulShots->Next();
        this->opponentBoard->SetCell(coord.first, coord.second, CellType::HIT);
    }
    this->NotifyObservers(&PlayerObserver::PostSuccessfulHits);
}

void GenericPlayer::EndGame(GameResult result, char *reason) {
    this->NotifyObservers(&PlayerObserver::PreEndGame);
    // Nothing needs to be done here!
    this->NotifyObservers(&PlayerObserver::PostEndGame);
}

// Protected:
void GenericPlayer::SetShips(Iterator<Ship> it) {
    while(it.HasNext()) {
        Ship nxtShip = it.Next();
        this->ships.push_back(nxtShip);
        Iterator<std::pair<int,int>> pts = nxtShip.GetPoints();
        while(pts.HasNext()) {
            std::pair<int,int> pt = pts.Next();
            this->myBoard->SetCell(pt.first, pt.second, CellType::SHIP);
        }
    }
}

void GenericPlayer::UpdateShots(Iterator<std::pair<int,int>> it) {
    while(it.HasNext()) {
        std::pair<int,int> pt = it.Next();
        this->opponentBoard->SetCell(pt.first, pt.second, CellType::MISS);
    }
}

int GenericPlayer::ShipsAlive() {
    int tot = 0;
    for(Ship s : ships) {
        Iterator<std::pair<int,int>> it = s.GetPoints();
        bool sunk = true;
        while(it.HasNext()) {
            std::pair<int,int> pt = it.Next();
            if(this->myBoard->GetCell(pt.first, pt.second) != CellType::HIT) {
                sunk = false;
                break;
            }
        }
        if(sunk) ++tot;
    }
    return ships.size() - tot;
}

// ObservablePlayer Interface overriding:
PlayerSnapshot *GenericPlayer::CreatePlayerSnapshot() {
    return new PlayerSnapshot(this->myBoard, this->opponentBoard, this->ships);
}