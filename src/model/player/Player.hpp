#pragma once

#include "../../util/Iterator.hpp"
#include "../../util/Map.hpp"
#include "../board/Ship.hpp"
#include "../GameResult.hpp"

namespace Model {    
    class Player {
    public:
        virtual ~Player() {};
        virtual const char* Name() = 0;
        virtual Iterator<Ship> Setup(int width, int height, Map<ShipType, int> *specifications) = 0;
        virtual Iterator<std::pair<int,int>> TakeShots() = 0;
        virtual Iterator<std::pair<int, int>> ReportDamage(Iterator<std::pair<int, int>> *opponentShots) = 0;
        virtual void SuccessfulHits(Iterator<std::pair<int,int>> *successfulShots) = 0;
        virtual void EndGame(GameResult result, char *reason) = 0;
    };
}