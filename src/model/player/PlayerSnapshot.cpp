#include "PlayerSnapshot.hpp"

using namespace Model;

PlayerSnapshot::PlayerSnapshot(Board *myBoard, Board *opBoard, Iterator<Ship> myShips) {
    this->myBoard = myBoard;
    this->opBoard = opBoard;
    this->myShips = myShips;
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