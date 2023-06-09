#include "PlayerSnapshot.hpp"
#include "ObservablePlayer.hpp"

using namespace Model;

PlayerSnapshot::PlayerSnapshot(const char* name, Board *myBoard, Board *opBoard, Iterator<Ship> myShips, const PlayerStatus status) {
    this->name = name;
    this->myBoard = myBoard;
    this->opBoard = opBoard;
    this->myShips = myShips;
    this->status = status;
}

const Board PlayerSnapshot::GetMyBoard() {
    return *this->myBoard;
}

Iterator<Ship> PlayerSnapshot::GetMyShips() {
    return this->myShips;
}

const Board PlayerSnapshot::GetOpponentBoard() {
    return *this->opBoard;
}

const char* PlayerSnapshot::GetName() {
    return this->name;
}

const PlayerStatus PlayerSnapshot::GetPlayerStatus() {
    return this->status;
}

