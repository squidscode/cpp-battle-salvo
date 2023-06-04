#pragma once

#include "../board/Board.hpp"
#include "../board/Ship.hpp"
#include "../../util/Iterator.hpp"

namespace Model {
    class PlayerSnapshot {
    public:
        virtual Board GetMyBoard() = 0;
        virtual Iterator<Ship> GetMyShips() = 0;
        virtual Board GetOpponentBoard() = 0;
    };
}