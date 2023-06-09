#pragma once

#include "../board/Board.hpp"
#include "../board/Ship.hpp"
#include "../../util/Iterator.hpp"
#include "PlayerStatus.hpp"

namespace Model {
    class PlayerSnapshot {
    public:
        PlayerSnapshot(const char* name, Board *myBoard, Board *opBoard, Iterator<Ship> myShips, const PlayerStatus status);

        virtual const Board GetMyBoard();
        virtual Iterator<Ship> GetMyShips();
        virtual const Board GetOpponentBoard();
        virtual const char* GetName();
        virtual const PlayerStatus GetPlayerStatus();
    private:
        const char *name;
        Board *myBoard;
        Board *opBoard;
        Iterator<Ship> myShips;
        PlayerStatus status;
    };
}