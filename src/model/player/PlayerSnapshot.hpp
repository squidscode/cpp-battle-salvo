#pragma once

#include "../board/Board.hpp"
#include "../board/Ship.hpp"
#include "../../util/Iterator.hpp"

namespace Model {
    class PlayerSnapshot {
    public:
        PlayerSnapshot(Board *myBoard, Board *opBoard, Iterator<Ship> myShips);

        virtual const Board GetMyBoard();
        virtual Iterator<Ship> GetMyShips();
        virtual const Board GetOpponentBoard();
    private:
        Board *myBoard;
        Board *opBoard;
        Iterator<Ship> myShips;
    };
}